import java.sql.*;
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

        //获取链接
        try {
            Connection_Pool pool = Pool_Factory.getPool();
            if (pool != null) {
                try (Connection connection = pool.getConnection()) {
                    PreparedStatement ps = null;
                    try {

                        //执行语句
                        ps = connection.prepareStatement(sql);
                        for (int i = 0; i < params.length; i++)
                            ps.setObject(i + 1, params[i]);

                        //返回影响的数据的条数
                        return ps.executeUpdate();

                    } catch (SQLException e) {
                        LOGGER.severe("Error executing SQL statement: " + e.getMessage());
                        return 0;
                    } finally {

                        //释放资源
                        pool.close(ps, connection);

                    }
                }
            }
        } catch (SQLException e) {
            LOGGER.severe("Error getting database connection: " + e.getMessage());
            return 0;
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

        //获取链接
        try {
            Connection_Pool pool = Pool_Factory.getPool();
            if (pool != null) {
                try (Connection connection = pool.getConnection()) {
                    PreparedStatement ps = null;
                    ResultSet rs = null;
                    try {

                        //执行语句
                        ps = connection.prepareStatement(sql);
                        for (int i = 0; i < params.length; i++)
                            ps.setObject(i + 1, params[i]);
                        rs=ps.executeQuery();
                        return handler.handle(rs);

                    } catch (SQLException e) {
                        LOGGER.severe("Error executing SQL statement: " + e.getMessage());
                        return null;
                    }finally {

                        //释放资源
                        pool.close(rs,ps, connection);

                    }
                }
            }
        } catch (SQLException e) {
            LOGGER.severe("Error getting database connection: " + e.getMessage());
            return null;
        }

        return null;
    }
}
