package com.hjf.tieba.util;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Logger;

public class CRUD_Utils {
    private static final Logger LOGGER = Logger.getLogger(CRUD_Utils.class.getName());
    private CRUD_Utils() {
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
        try (Connection connection = Connection_Pool.getConnection()) {
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
                ps.close();
               connection.close();

            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

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
                try (Connection connection = Connection_Pool.getConnection()) {
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
                        rs.close();
                        ps.close();
                        connection.close();

                    }
                }
        } catch (SQLException e) {
            LOGGER.severe("Error getting database connection: " + e.getMessage());
            return null;
        }

    }
}
