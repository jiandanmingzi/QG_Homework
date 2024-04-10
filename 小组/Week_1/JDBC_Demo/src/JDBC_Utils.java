
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;
import java.util.logging.Logger;

public class JDBC_Utils {
    private static final Logger LOGGER = Logger.getLogger(JDBC_Utils.class.getName());
    private static final String userName;
    private static final String passWord;
    private static final String url;
    static {
        //加载配置文件
        Properties prop = new Properties();
        InputStream input=null;
        try {
            input = JDBC_Utils.class.getClassLoader().getResourceAsStream("config.properties");
            prop.load(input);
        } catch (IOException e) {
            LOGGER.severe("Error closing input stream: " + e.getMessage());
        }

        //获取配置
        url=prop.getProperty("url");
        userName=prop.getProperty("userName");
        passWord=prop.getProperty("passWord");
        String driver=prop.getProperty("driver");

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
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, userName, passWord);
    }
}

