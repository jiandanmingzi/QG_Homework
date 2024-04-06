package com.hjf.tieba.controller;

import com.hjf.tieba.entity.User;
import com.hjf.tieba.service.UserService;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/loginServlet")
public class loginServlet extends HttpServlet {
    private final UserService service=new UserService();
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws javax.servlet.ServletException, java.io.IOException {
        String userName = request.getParameter("userName");
        String passWord = request.getParameter("passWord");
        String userAccount = request.getParameter("userAccount");
        User user = service.login(userName, passWord,userAccount);
        if (user!= null) {
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
            response.sendRedirect("home.html");
        }else{
            request.setAttribute("log_msg","用户名或密码错误");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws javax.servlet.ServletException, java.io.IOException {
        doGet(request,response);
    }
}