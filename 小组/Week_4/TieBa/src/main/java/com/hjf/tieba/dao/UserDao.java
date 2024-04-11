package com.hjf.tieba.dao;

import com.hjf.tieba.entity.User;

public interface UserDao {
    public User selectUser(String userAccount, String password);
    public boolean addUser(String userAccount, String password,String userName);
    public boolean deleteUser(User user);
    public boolean updateUser(String userAccount, String password,String userName);
    public boolean checkAccount(String userAccount);
}
