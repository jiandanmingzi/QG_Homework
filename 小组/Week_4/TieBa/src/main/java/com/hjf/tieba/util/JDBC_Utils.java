package com.hjf.tieba.util;

import com.hjf.tieba.config.ConfigReader;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.logging.Logger;

public class JDBC_Utils {
    private static final Logger LOGGER = Logger.getLogger(JDBC_Utils.class.getName());
    private static final String userName;
    private static final String passWord;
    private static final String url;

    static {
        //获取配置
        url= ConfigReader.url;
        userName= ConfigReader.userName;
        passWord= ConfigReader.passWord;
        String driver= ConfigReader.driver;

        //加载驱动
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            LOGGER.severe("Error loading JDBC driver: " + e.getMessage());
        }
    }

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, userName, passWord);
    }

    private JDBC_Utils(){
        throw new IllegalStateException("");
    }
}
