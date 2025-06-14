package org.example.model;

import lombok.*;

@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Hall {
    private int number;
    private int seatCount;
    private double screenDiameterFeet;
    private boolean supports3D;
}

