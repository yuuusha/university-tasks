package org.example.viewmodel;

import lombok.Getter;
import org.example.model.HallOccupancy;
import org.example.model.Session;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

@Getter
public class HallOccupancyViewModel {

    private List<HallOccupancy> occupancies = new ArrayList<>();

    public HallOccupancyViewModel(List<HallOccupancy> initialOccupancies) {
        this.occupancies = new ArrayList<>();
        if (initialOccupancies != null) {
            this.occupancies.addAll(initialOccupancies);
        }
    }

    public boolean bookSeat(Session session, int seatNumber) {
        if (session == null || session.getHall() == null) return false;

        int totalSeats = session.getHall().getSeatCount();

        if (seatNumber < 1 || seatNumber > totalSeats) {
            return false;
        }

        boolean alreadyOccupied = occupancies.stream()
                .anyMatch(o -> o.getSession().equals(session) && o.getOccupiedSeatNumber() == seatNumber);

        if (alreadyOccupied) {
            return false;
        }

        occupancies.add(new HallOccupancy(session, seatNumber));
        return true;
    }


    public int getFreeSeatsCountForSession(Session session) {
        if (session == null || session.getHall() == null) return 0;

        int totalSeats = session.getHall().getSeatCount();

        long occupiedCount = occupancies.stream()
                .filter(o -> o.getSession().equals(session))
                .count();

        return totalSeats - (int) occupiedCount;
    }

    public List<Integer> getOccupiedSeatsForSession(Session session) {
        return occupancies.stream()
                .filter(o -> o.getSession().equals(session))
                .map(HallOccupancy::getOccupiedSeatNumber)
                .sorted()
                .collect(Collectors.toList());
    }
}

