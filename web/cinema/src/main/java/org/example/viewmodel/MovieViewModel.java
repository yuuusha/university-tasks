package org.example.viewmodel;

import lombok.Getter;
import org.example.model.Movie;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

@Getter
public class MovieViewModel {

    private final List<Movie> movies;
    private long nextId = 1;

    public MovieViewModel(List<Movie> initialMovies) {
        this.movies = new ArrayList<>();
        if (initialMovies != null) {
            this.movies.addAll(initialMovies);
            this.nextId = initialMovies.stream()
                    .mapToLong(Movie::getId)
                    .max()
                    .orElse(0) + 1;
        }
    }

    public boolean addMovie(String author, String title, Duration duration) {
        if (author == null || title == null || duration == null) {
            return false;
        }
        movies.add(new Movie(nextId++, author, title, duration));
        return true;
    }

    public Movie getMovieById(Long id) {
        return movies.stream()
                .filter(movie -> movie.getId().equals(id))
                .findFirst()
                .orElse(null);
    }
}

