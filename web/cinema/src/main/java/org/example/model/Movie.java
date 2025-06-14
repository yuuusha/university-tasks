package org.example.model;

import lombok.*;

import java.time.Duration;

@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Movie {
    private Long id;
    private String author;
    private String title;
    private Duration duration;
}

