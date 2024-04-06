package com.hjf.tieba.util;

import com.alibaba.druid.pool.DruidDataSource;


import java.sql.Connection;
import java.sql.SQLException;

public class Connection_Pool {
    public static DruidDataSource dataSource;
    static {
        // 创建Druid数据源
        dataSource = new DruidDataSource();

        // 设置数据库连接信息
        dataSource.setUrl("jdbc:mysql://localhost:3306/tieba");
        dataSource.setUsername("root");
        dataSource.setPassword("Jiandanmima1/");

        // 配置连接池参数
        dataSource.setInitialSize(5); // 初始化连接数
        dataSource.setMaxActive(20);  // 最大连接数
        dataSource.setMinIdle(5);    // 最小空闲连接数
    }
    public static Connection getConnection() throws SQLException {
        return dataSource.getConnection();
    }
}
