package com.hjf.tieba.util;

import java.sql.ResultSet;
import java.sql.SQLException;

public interface MyHandler<T> {
        T handle(ResultSet rs) throws SQLException;
}
