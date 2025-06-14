package org.example.model;

import lombok.*;

import java.time.LocalDateTime;

@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Session {
    private Long id;
    private Movie movie;
    private LocalDateTime time;
    private Hall hall;
    private double price;
}

