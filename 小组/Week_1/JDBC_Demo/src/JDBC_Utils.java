import java.sql.*;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.logging.Logger;
public class JDBC_Utils {
    private static final Logger LOGGER = Logger.getLogger(CURD_Utils.class.getName());
    private static final String userName;
    private static final String password;
    private static final String url;

    private JDBC_Utils() {
        throw new AssertionError("This class should not be instantiated.");
    }

    static {
        //加载配置文件
        Properties prop = new Properties();
        InputStream input=null;
        try {
            input = new FileInputStream("config.properties");
            prop.load(input);
        } catch (IOException e) {
            LOGGER.severe("Error closing input stream: " + e.getMessage());
        }

        //获取配置
        url=prop.getProperty("tableName");
        userName=prop.getProperty("userName");
        password=prop.getProperty("password");
        String driver=prop.getProperty("localHost");

        //加载驱动
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            LOGGER.severe("Error loading JDBC driver: " + e.getMessage());
        }

        try {
            if (input != null)
                input.close();
        } catch (IOException e) {
            LOGGER.severe("Error closing input stream: " + e.getMessage());
        }
    }

    //获取链接
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, userName, password);
    }

    //释放资源
    public static void close(ResultSet rs,PreparedStatement ps, Connection connection) throws SQLException {
        if (rs!= null)
            rs.close();
        if (ps!= null)
            ps.close();
        if (connection!= null)
            connection.close();
    }

    public static void close(PreparedStatement ps, Connection connection) throws SQLException {
        if (ps!= null)
            ps.close();
        if (connection!= null)
            connection.close();
    }
    public static void close(ResultSet rs,PreparedStatement ps) throws SQLException {
        if (rs!= null)
            rs.close();
        if (ps!= null)
            ps.close();
    }
    public static void close(PreparedStatement ps) throws SQLException {
        if (ps!= null)
            ps.close();
    }
}
