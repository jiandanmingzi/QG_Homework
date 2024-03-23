import java.sql.SQLException;

public class Pool_Factory {
    private volatile static Connection_Pool pool=null;

    private Pool_Factory(){}
    public static Connection_Pool getPool() throws SQLException {
        if (pool==null){
            synchronized (Pool_Factory.class){
                if (pool==null){
                    pool=new Connection_Pool();
                    pool.init();
                }else{
                    return pool;
                }
            }
        }else
            return  pool;
        return null;
    }
}
