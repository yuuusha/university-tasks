package org.example.authorizationservice.controller;

import org.example.authorizationservice.domain.dto.AuthUserRequest;
import org.example.authorizationservice.service.AuthService;
import org.example.authorizationservice.service.TokenService;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import java.util.Optional;

@RestController
@RequiredArgsConstructor
public class AuthController {

    private final AuthService authService;

    private final TokenService tokenService;

    @PostMapping("/sign-up")
    @ResponseStatus(HttpStatus.CREATED)
    public void signUp(@RequestBody AuthUserRequest authUserRequest) {
        authService.registerUser(authUserRequest.usr(), authUserRequest.pwd());
    }

    @PostMapping("/auth")
    @ResponseStatus(HttpStatus.OK)
    public void auth(@RequestBody Optional<AuthUserRequest> authUserRequest, HttpServletRequest request, HttpServletResponse response) {
        if (authUserRequest.isPresent()) {
            authService.authenticateUser(authUserRequest.get().usr(), authUserRequest.get().pwd(), response);
        } else {
            authService.authenticateUser(request, response);
        }
    }

    @PostMapping("/refresh")
    @ResponseStatus(HttpStatus.OK)
    public void refresh(HttpServletRequest request, HttpServletResponse response) {
        tokenService.refreshTokens(request, response);
    }
}
