import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.Queue;
import java.sql.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.LinkedList;
import java.util.logging.Logger;

public class Connection_Pool {
    private static final Logger LOGGER = Logger.getLogger(CURD_Utils.class.getName());

    private static final int maxConnections;
    public static volatile boolean inited =false;
    volatile Queue<Connection> connections ;
    private final ReentrantLock lock=new ReentrantLock();

    public Connection_Pool(){}

    static{
        //加载配置文件
        Properties prop = new Properties();
        InputStream input;
        try {
            input = new FileInputStream("config.properties");
            prop.load(input);
        } catch (IOException e) {
            LOGGER.severe("Error closing input stream: " + e.getMessage());
        }
        maxConnections = Integer.parseInt(prop.getProperty("maxConnections")) ;
    }


    public void init() throws SQLException {
        if(!inited){
            if(!lock.isLocked()){
                lock.lock();
                try {
                    if (!inited) {
                        connections = new LinkedList<>();
                            for (int i = 0; i < maxConnections; i++)
                                connections.add(JDBC_Utils.getConnection());

                        inited = true;
                    }
                }finally{
                    lock.unlock();
                }
            }
        }
    }


    public Connection getConnection() throws SQLException {
        Connection connection =null;
        if (!connections.isEmpty()){
            if(!lock.isLocked()){
                lock.lock();
                try{
                    if (!connections.isEmpty()){
                        connection = connections.remove();
                    }else{
                        connection = JDBC_Utils.getConnection();
                    }
                }finally{
                    lock.unlock();
                }
            }
        }else{
                connection = JDBC_Utils.getConnection();
        }
        return connection;
    }

    public void close(PreparedStatement ps, Connection connection) throws SQLException {
        if (connections.size() < maxConnections){
            if(!lock.isLocked()){
                lock.lock();
                if (connections.size() < maxConnections){
                    connections.add(connection);
                    JDBC_Utils.close(ps);
                }else
                    JDBC_Utils.close(ps,connection);
            }
        }else
            JDBC_Utils.close(ps,connection);

    }

    public void close(ResultSet rs,PreparedStatement ps, Connection connection) throws SQLException {
        if (connections.size() < maxConnections){
            if(!lock.isLocked()){
                lock.lock();
                if (connections.size() < maxConnections){
                    connections.add(connection);
                    JDBC_Utils.close(rs,ps);
                }else
                    JDBC_Utils.close(rs,ps,connection);
            }
        }else
            JDBC_Utils.close(rs,ps,connection);

    }
}
