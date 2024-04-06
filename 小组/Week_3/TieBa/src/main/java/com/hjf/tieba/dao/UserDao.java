package com.hjf.tieba.dao;

import com.hjf.tieba.entity.User;

public class UserDao {
    public User selectUser(String userAccount, String password) {
        return null;
    }
    public boolean addUser(String userAccount, String password,String userName) {
        return true;
    }
    public boolean deleteUser(User user) {
        return true;
    }
    public boolean updateUser(String userAccount, String password,String userName){
        return true;
    }
}
