package com.hjf.tieba.service;

import com.hjf.tieba.entity.User;

public interface UserService {
    public User login( String password, String userAccount);
    public boolean signup(String password, String userAccount,String userName);
    public boolean checkAccount(String userAccount);
}
