
import java.sql.*;
import java.util.List;
import java.util.logging.Logger;

public class MyHandler<T> {
    String name;
    T value;
    private static final Logger LOGGER = Logger.getLogger(CURD_Utils.class.getName());

    public MyHandler(String names) {
        this.name = names;
    }
    public void handle(ResultSet rs) throws SQLException {
        if (value instanceof List){
            ((List)value).add(rs.getObject(name));
        }else {
            try {
                value = (T) rs.getObject(name);
            } catch (SQLException e) {
                LOGGER.severe(e.getMessage());
            }
        }
    }
}
