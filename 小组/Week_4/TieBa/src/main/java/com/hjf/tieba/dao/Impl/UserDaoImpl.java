package com.hjf.tieba.dao.Impl;

import com.hjf.tieba.dao.UserDao;
import com.hjf.tieba.entity.User;
import com.hjf.tieba.util.CRUD_Utils;

import java.sql.ResultSet;

public class UserDaoImpl implements UserDao {
    User user = null;
    @Override
    public User selectUser(String userAccount, String password) {
        if (user == null) {String sql = "SELECT * FROM user WHERE account = ? AND password = ?";
            user = CRUD_Utils.query(sql , rs -> {
                if (rs.next()) {
                    User user = new User();
                    user.Id = rs.getInt("id");
                    user.account = rs.getString("account");
                    user.userName = rs.getString("username");
                    user.password= rs.getString("password");
                    user.CreatedDate = rs.getTimestamp("created_at");
                    user.likes = rs.getInt("likes");
                    return user;
                }
                return null;
            }, userAccount, password);
        }else {
            if ((user.account.equals(userAccount))&&(user.password.equals(password)))
                return user;
            else
                return null;
        }
        return user;
    }
    @Override
    public boolean addUser(String userAccount, String password,String userName) {
        String sql = "INSERT INTO user(account,password,username,likes,created_at) VALUES(?,?,?,?,NOW())";
        return (CRUD_Utils.update(sql, userAccount, password, userName, 0)==1);
    }
    @Override
    public boolean deleteUser(User user) {
        return true;
    }
    @Override
    public boolean updateUser(String userAccount, String password,String userName){
        return true;
    }
    @Override
    public boolean checkAccount(String userAccount)
    {
        String sql = "SELECT id FROM user where account = ?";
        return Boolean.TRUE.equals(CRUD_Utils.query(sql, ResultSet::next, userAccount));
    }
    public UserDaoImpl() {}
}
