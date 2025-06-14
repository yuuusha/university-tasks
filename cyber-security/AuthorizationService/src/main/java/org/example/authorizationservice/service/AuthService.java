package org.example.authorizationservice.service;

import org.example.authorizationservice.domain.model.User;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class AuthService {

    private final UserService userService;

    private final TokenService tokenService;

    public void registerUser(String username, String password) {
        userService.registerUser(username, password);
    }

    public void authenticateUser(String username, String password, HttpServletResponse response) {
        User user = userService.authenticateUser(username, password);
        tokenService.addAuthCookiesToResponse(user, response);
    }

    public void authenticateUser(HttpServletRequest request, HttpServletResponse response) {
        tokenService.validateAuthToken(request);
    }
}
