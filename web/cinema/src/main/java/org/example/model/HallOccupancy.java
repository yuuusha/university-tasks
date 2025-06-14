package org.example.model;

import lombok.*;

@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class HallOccupancy {
    private Session session;
    private int occupiedSeatNumber;
}

