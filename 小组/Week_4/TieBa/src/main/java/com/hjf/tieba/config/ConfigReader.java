package com.hjf.tieba.config;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.logging.Logger;

public class ConfigReader {
    private static final Logger LOGGER = Logger.getLogger(ConfigReader.class.getName());
    public static final String driver;
    public static final String url;
    public static final String userName;
    public static final String passWord;
    public static final int maxConnections;
    static {
        InputStream in = ConfigReader.class.getClassLoader().getResourceAsStream("config.properties");
        Properties properties = new Properties();
        try {
            properties.load(in);
        } catch (IOException e) {
            LOGGER.severe("Error loading config properties:"+e.getMessage());
        }
        driver = properties.getProperty("driver");
        url = properties.getProperty("url");
        userName = properties.getProperty("userName");
        passWord = properties.getProperty("passWord");
        maxConnections = Integer.parseInt(properties.getProperty("maxConnections"));
        if (in != null) {
            try {
                in.close();
            } catch (IOException e) {
                LOGGER.severe("Error closing input stream:" + e.getMessage());
            }
        }
    }

    private ConfigReader(){
        throw new IllegalStateException();
    }
}
