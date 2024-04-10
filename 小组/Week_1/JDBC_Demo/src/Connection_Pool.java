import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.Properties;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Logger;

public class Connection_Pool {
    private static final Logger LOGGER = Logger.getLogger(Connection_Pool.class.getName());
    static volatile Queue<Connection> connections = new LinkedList<Connection>();
    private static final ReentrantLock lock = new ReentrantLock();
    private static final int maxConnections;
    static {
        //加载配置文件
        Properties prop = new Properties();
        InputStream input;
        try {
            input = Connection_Pool.class.getClassLoader().getResourceAsStream("config.properties");
            prop.load(input);
        } catch (IOException e) {
            LOGGER.severe("Error loading config.properties: " + e.getMessage());
        }
        maxConnections = Integer.parseInt(prop.getProperty("maxConnections"));
        for (int i = 0; i < maxConnections; i++)
        {
            try {
                connections.add(JDBC_Utils.getConnection());
            } catch (SQLException e) {
                LOGGER.severe("Error getting connection: " + e.getMessage());
            }
        }
    }
    public static Connection getConnection() throws SQLException {
        Connection connection = null;
        if (connections.isEmpty())
            connection = JDBC_Utils.getConnection();
        else {
            try {
                if (lock.tryLock(1, TimeUnit.SECONDS))
                {
                    try
                    {
                        if (connections.isEmpty())
                            connection = JDBC_Utils.getConnection();
                        else
                            connection = connections.poll();
                    }finally {
                        lock.unlock();
                    }
                }else connection = JDBC_Utils.getConnection();
            } catch (InterruptedException e) {
                LOGGER.severe("Error getting lock: " + e.getMessage());
            }
        }
        return connection;
    }
    public static void returnConnection(Connection connection) throws SQLException {
        if (connection!= null) {
            if (connections.size()<maxConnections)
                try {
                    if (lock.tryLock(1, TimeUnit.SECONDS))
                    {
                        if (connections.size()<maxConnections)
                            try {
                                connections.add(connection);
                            } finally {
                                lock.unlock();
                            }
                        else connection.close();
                    }
                } catch (InterruptedException e) {
                    LOGGER.severe("Error getting lock: " + e.getMessage());
                }
            else connection.close();
        }
    }
}

