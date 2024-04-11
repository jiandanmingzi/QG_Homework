package com.hjf.tieba.service.Impl;

import com.hjf.tieba.dao.Impl.UserDaoImpl;
import com.hjf.tieba.dao.UserDao;
import com.hjf.tieba.entity.User;
import com.hjf.tieba.service.UserService;

public class UserServiceImpl implements UserService {
    UserDao userDao = new UserDaoImpl();
    @Override
    public User login(String password, String userAccount) {
        return this.userDao.selectUser(userAccount, password);
    }

    @Override
    public boolean signup(String password, String userAccount,String userName) {
        if (this.checkAccount(userAccount))
            return false;
        return userDao.addUser(userAccount, password, userName);
    }

    @Override
    public boolean checkAccount(String userAccount) {
        return this.userDao.checkAccount(userAccount);
    }
}
