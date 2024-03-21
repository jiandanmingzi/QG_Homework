import com.mysql.cj.callback.MysqlCallbackHandler;

import java.sql.*;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.logging.Logger;
final public class CURD_Utils {
    private static final Logger LOGGER = Logger.getLogger(CURD_Utils.class.getName());
    private CURD_Utils() {
        throw new AssertionError("This class should not be instantiated.");
    }


    public static int update(String sql,Object... params){

        //获取sql语句中的占位符数量
        long cnt=  sql.chars()
                .filter(c->c=='?')
                .count();

        //比较占位符数量是否与可变参数数量相同
        if(cnt!=params.length){
            LOGGER.severe("The number of placeholder should be the same as the number of params");
            return 0;
        }

        String tableName;
        String userName;
        String password;
        String localHost;
        Properties prop = new Properties();
        InputStream input=null;

        //获取配置
    try {
            input = new FileInputStream("config.properties");
            prop.load(input);
            tableName=prop.getProperty("tableName");
            userName=prop.getProperty("userName");
            password=prop.getProperty("password");
            localHost=prop.getProperty("localHost");
        } catch (IOException e) {
            LOGGER.severe("Error loading properties file: " + e.getMessage());
            return 0;
        } finally {
            if (input!= null) {
                try {
                    input.close();
                } catch (IOException e) {
                    LOGGER.severe("Error closing input stream: " + e.getMessage());
                }
            }
        }

        //加载驱动
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            LOGGER.severe("Error loading JDBC driver: " + e.getMessage());
            return 0;
        }

        //准备执行语句
        try {
            //获取链接
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:"+localHost+"/"+tableName, userName, password);
            PreparedStatement ps = null;
            try {
                //执行语句
                ps = connection.prepareStatement(sql);
                for (int i = 0; i < params.length; i++) {
                    ps.setObject(i + 1, params[i]);
                }
                //返回影响的数据的条数
                return ps.executeUpdate();
            } catch (SQLException e) {
                LOGGER.severe("Error executing SQL statement: " + e.getMessage());
            } finally {
                //释放资源
                if (ps != null)
                    ps.close();
                connection.close();
            }
        }catch(SQLException e){
            LOGGER.severe("Error getting database connection: " + e.getMessage());
        }

        return 0;
    }

    public static <T> T query(String sql,MyHandler<T> handler, Object... params){
        //获取sql语句中的占位符数量
        long cnt=  sql.chars()
                .filter(c->c=='?')
                .count();

        //比较占位符数量是否与可变参数数量相同
        if(cnt!=params.length){
            LOGGER.severe("The number of placeholder should be the same as the number of params");
            return null;
        }

        String tableName;
        String userName;
        String password;
        String localHost;
        Properties prop = new Properties();
        InputStream input=null;

        //获取配置
        try {
            input = new FileInputStream("config.properties");
            prop.load(input);
            tableName=prop.getProperty("tableName");
            userName=prop.getProperty("userName");
            password=prop.getProperty("password");
            localHost=prop.getProperty("localHost");
        } catch (IOException e) {
            LOGGER.severe("Error loading properties file: " + e.getMessage());
            return null;
        } finally {
            if (input!= null) {
                try {
                    input.close();
                } catch (IOException e) {
                    LOGGER.severe("Error closing input stream: " + e.getMessage());
                }
            }
        }

        //加载驱动
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            LOGGER.severe("Error loading JDBC driver: " + e.getMessage());
            return null;
        }

        //准备执行语句
        try {
            //获取链接
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:"+localHost+"/"+tableName, userName, password);
            PreparedStatement ps = null;
            ResultSet rs = null;
            try {
                //执行语句
                ps = connection.prepareStatement(sql);
                for (int i = 0; i < params.length; i++)
                    ps.setObject(i + 1, params[i]);
                try{
                    rs = ps.executeQuery();
                    while (rs.next())
                        handler.handle(rs);
                    return handler.value;
                }catch (SQLException e){
                }finally {
                    //释放资源
                    if (rs != null)
                        rs.close();
                    if (ps != null)
                        ps.close();
                    connection.close();
                }
            } catch (SQLException e) {
                LOGGER.severe("Error executing SQL statement: " + e.getMessage());
            }
        }catch(SQLException e){
            LOGGER.severe("Error getting database connection: " + e.getMessage());
        }

        return null;
    }
}
