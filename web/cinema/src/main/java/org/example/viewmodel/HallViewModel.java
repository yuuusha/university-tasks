package org.example.viewmodel;

import lombok.Getter;
import org.example.model.Hall;

import java.util.ArrayList;
import java.util.List;

@Getter
public class HallViewModel {

    private List<Hall> halls = new ArrayList<>();

    public HallViewModel(List<Hall> initialHalls) {
        this.halls = new ArrayList<>();
        if (initialHalls != null) {
            this.halls.addAll(initialHalls);
        }
    }

    public Hall getHallByNumber(int number) {
        return halls.stream()
                .filter(hall -> hall.getNumber() == number)
                .findFirst()
                .orElse(null);
    }
}

