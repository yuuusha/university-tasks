package org.example.viewmodel;

import lombok.Getter;
import org.example.model.Hall;
import org.example.model.Movie;
import org.example.model.Session;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Getter
public class SessionViewModel {

    private final List<Session> sessions;
    private long nextId = 1;

    public SessionViewModel(List<Session> initialSessions) {
        this.sessions = new ArrayList<>();
        if (initialSessions != null) {
            this.sessions.addAll(initialSessions);
            this.nextId = initialSessions.stream()
                    .mapToLong(Session::getId)
                    .max()
                    .orElse(0) + 1;
        }
    }

    public boolean addSession(Movie movie, LocalDateTime time, Hall hall, double price) {
        if (movie == null || time == null || hall == null) {
            return false;
        }

        LocalDateTime newStart = time;
        LocalDateTime newEnd = time.plus(movie.getDuration());

        for (Session existing : sessions) {
            if (!existing.getHall().equals(hall)) continue;

            LocalDateTime existingStart = existing.getTime();
            LocalDateTime existingEnd = existingStart.plus(existing.getMovie().getDuration());

            boolean overlaps = !(newEnd.isBefore(existingStart) || newStart.isAfter(existingEnd));
            if (overlaps) {
                return false;
            }
        }

        sessions.add(new Session(nextId++, movie, time, hall, price));
        return true;
    }

    public Session getSessionById(Long id) {
        return sessions.stream()
                .filter(session -> session.getId().equals(id))
                .findFirst()
                .orElse(null);
    }

}

