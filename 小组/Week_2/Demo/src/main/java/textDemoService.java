import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/textDemo")
public class textDemoService implements Servlet {
    @Override
    public void init(ServletConfig config) throws ServletException {
        System.out.println("inited");
    }

    @Override
    public ServletConfig getServletConfig() {
        return null;
    }

    @Override
    public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException {
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;
        String method = request.getMethod();
        if (method.equals("GET")) {
            doGet(request, response);
        } else if (method.equals("POST")) {
            doPost(request, response);
        } else if (method.equals("PUT")) {
            doPut(request, response);
        } else if (method.equals("DELETE")) {
            doDelete(request,response);
        } else if (method.equals("HEAD")) {
            doHead(request,response);
        } else if (method.equals("OPTIONS")) {
            doOptions(request,response);
        } else if (method.equals("TRACE")) {
            doTrace(request,response);
        } else if (method.equals("CONNECT")) {
            doConnect(request, response);
        }else{
            System.out.println("1");
            response.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
        }
        getRequest(request, response);
    }

    @Override
    public String getServletInfo() {
        return null;
    }

    @Override
    public void destroy() {

    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO POST...");
    }
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO GET...");
    }
    public void doPut(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO PUT...");
    }
    public void doDelete(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO DELETE...");
    }
    public void doHead(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO HEAD...");
    }
    public void doOptions(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO OPTIONS...");
    }
    public void doTrace(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO TRACE...");
    }
    public void doConnect(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("DO CONNECT...");
    }
    public void getRequest(HttpServletRequest request, HttpServletResponse response){
        String value = request.getHeader("Responsecode");
        System.out.println("Request for response code:"+value);
        response.setStatus(Integer.parseInt(value));
    }
}
