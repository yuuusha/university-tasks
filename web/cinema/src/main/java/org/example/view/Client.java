package org.example.view;

import org.example.model.Hall;
import org.example.model.Movie;
import org.example.model.Session;
import org.example.model.HallOccupancy;
import org.example.viewmodel.HallOccupancyViewModel;
import org.example.viewmodel.HallViewModel;
import org.example.viewmodel.MovieViewModel;
import org.example.viewmodel.SessionViewModel;
import org.teavm.jso.browser.Window;
import org.teavm.jso.dom.html.*;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.List;

public class Client {

    private static HTMLSelectElement sessionSelect;
    private static HTMLSelectElement movieSelect;

    private static final MovieViewModel movieViewModel = new MovieViewModel(List.of(
            new Movie(1L, "Кристофер Нолан", "Начало", Duration.ofMinutes(148)),
            new Movie(2L, "Дени Вильнёв", "Дюна", Duration.ofMinutes(155)),
            new Movie(3L, "Джеймс Кэмерон", "Аватар", Duration.ofMinutes(162))
    ));

    private static final HallViewModel hallViewModel = new HallViewModel(List.of(
            new Hall(1, 100, 35.0, true),
            new Hall(2, 80, 28.5, false)
    ));

    private static final SessionViewModel sessionViewModel = new SessionViewModel(List.of(
            new Session(101L, movieViewModel.getMovieById(1L), LocalDateTime.of(2025, 3, 25, 18, 0), hallViewModel.getHallByNumber(1), 500),
            new Session(102L, movieViewModel.getMovieById(2L), LocalDateTime.of(2025, 3, 25, 20, 30), hallViewModel.getHallByNumber(2), 450)
    ));

    private static final HallOccupancyViewModel occupancyViewModel = new HallOccupancyViewModel(List.of(
            new HallOccupancy(sessionViewModel.getSessionById(101L), 1),
            new HallOccupancy(sessionViewModel.getSessionById(101L), 2),
            new HallOccupancy(sessionViewModel.getSessionById(102L), 5),
            new HallOccupancy(sessionViewModel.getSessionById(102L), 10)
    ));

    public static void main(String[] args) {
        HTMLDocument document = HTMLDocument.current();

        HTMLElement header = document.createElement("h1");
        header.appendChild(document.createTextNode("Кинотеатр"));
        document.getBody().appendChild(header);

        HTMLElement moviesList = document.createElement("ul");
        HTMLElement hallsList = document.createElement("ul");
        HTMLElement sessionsList = document.createElement("ul");

        document.getBody().appendChild(document.createElement("h2").appendChild(document.createTextNode("Фильмы")));
        document.getBody().appendChild(moviesList);
        document.getBody().appendChild(document.createElement("h2").appendChild(document.createTextNode("Залы")));
        document.getBody().appendChild(hallsList);
        document.getBody().appendChild(document.createElement("h2").appendChild(document.createTextNode("Сеансы")));
        document.getBody().appendChild(sessionsList);

        document.getBody().appendChild(createMovieForm(moviesList));
        document.getBody().appendChild(createSessionForm(sessionsList));

        document.getBody().appendChild(document.createElement("br"));

        sessionSelect = (HTMLSelectElement) document.createElement("select");
        document.getBody().appendChild(document.createElement("h2").appendChild(document.createTextNode("Бронирование мест")));
        document.getBody().appendChild(createBookingForm(sessionSelect, sessionsList));

        document.getBody().appendChild(createOccupiedSeatsButton());

        updateMoviesList(moviesList);
        updateHallsList(hallsList);
        updateSessionsList(sessionsList);
    }

    private static HTMLElement createMovieForm(HTMLElement moviesList) {
        HTMLDocument document = HTMLDocument.current();
        HTMLElement form = document.createElement("div");

        HTMLInputElement authorInput = (HTMLInputElement) document.createElement("input");
        authorInput.setPlaceholder("Автор");

        HTMLInputElement titleInput = (HTMLInputElement) document.createElement("input");
        titleInput.setPlaceholder("Название");

        HTMLInputElement durationInput = (HTMLInputElement) document.createElement("input");
        durationInput.setPlaceholder("Длительность (в минутах)");

        HTMLElement button = createButton("Добавить фильм", () -> {
            try {
                String author = authorInput.getValue();
                String title = titleInput.getValue();
                int minutes = Integer.parseInt(durationInput.getValue());

                boolean success = movieViewModel.addMovie(author, title, Duration.ofMinutes(minutes));
                if (!success) {
                    Window.alert("Ошибка: фильм с такими параметрами уже существует или некорректен.");
                    return;
                }

                updateMoviesList(moviesList);
                updateMovieSelect(movieSelect);
            } catch (Exception e) {
                Window.alert("Ошибка: проверьте корректность ввода.");
            }
        });

        form.appendChild(authorInput);
        form.appendChild(titleInput);
        form.appendChild(durationInput);
        form.appendChild(button);

        return form;
    }

    private static HTMLElement createSessionForm(HTMLElement sessionsList) {
        HTMLDocument document = HTMLDocument.current();
        HTMLElement form = document.createElement("div");

        movieSelect = (HTMLSelectElement) document.createElement("select");
        updateMovieSelect(movieSelect);

        HTMLSelectElement hallSelect = (HTMLSelectElement) document.createElement("select");
        for (Hall hall : hallViewModel.getHalls()) {
            HTMLOptionElement option = (HTMLOptionElement) document.createElement("option");
            option.setValue(String.valueOf(hall.getNumber()));
            option.appendChild(document.createTextNode("Зал " + hall.getNumber()));
            hallSelect.appendChild(option);
        }

        HTMLInputElement priceInput = (HTMLInputElement) document.createElement("input");
        priceInput.setPlaceholder("Цена");

        HTMLInputElement dateInput = (HTMLInputElement) document.createElement("input");
        dateInput.setPlaceholder("Дата");

        HTMLInputElement timeOnlyInput = (HTMLInputElement) document.createElement("input");
        timeOnlyInput.setPlaceholder("Время");

        HTMLElement button = createButton("Добавить сеанс", () -> {
            try {
                Long movieId = Long.parseLong(movieSelect.getValue());
                int hallNumber = Integer.parseInt(hallSelect.getValue());
                double price = Double.parseDouble(priceInput.getValue());

                String dateStr = dateInput.getValue();
                String timeStr = timeOnlyInput.getValue();
                LocalDateTime dateTime = LocalDateTime.parse(dateStr + "T" + timeStr);

                Movie movie = movieViewModel.getMovieById(movieId);
                Hall hall = hallViewModel.getHallByNumber(hallNumber);

                if (movie != null && hall != null) {
                    boolean success = sessionViewModel.addSession(movie, dateTime, hall, price);
                    if (!success) {
                        Window.alert("Ошибка: сеанс пересекается по времени с другим сеансом в этом зале.");
                        return;
                    }
                    updateSessionsList(sessionsList);
                } else {
                    Window.alert("Фильм или зал не найдены");
                }
            } catch (Exception e) {
                Window.alert("Ошибка: проверьте правильность заполнения даты, времени и цены.");
            }
        });

        form.appendChild(movieSelect);
        form.appendChild(hallSelect);
        form.appendChild(priceInput);
        form.appendChild(dateInput);
        form.appendChild(timeOnlyInput);
        form.appendChild(button);

        return form;
    }

    private static HTMLElement createButton(String text, Runnable onClick) {
        HTMLDocument document = HTMLDocument.current();
        HTMLElement button = document.createElement("button");
        button.appendChild(document.createTextNode(text));
        button.addEventListener("click", evt -> onClick.run());
        return button;
    }

    private static void updateSessionDropdown(HTMLSelectElement sessionSelect) {
        sessionSelect.setInnerHTML("");

        for (Session session : sessionViewModel.getSessions()) {
            HTMLOptionElement option = (HTMLOptionElement) HTMLDocument.current().createElement("option");
            option.setValue(session.getId().toString());
            option.appendChild(HTMLDocument.current().createTextNode(
                    "ID: " + session.getId() + " | " + session.getMovie().getTitle() + " (" + session.getTime() + ")"
            ));
            sessionSelect.appendChild(option);
        }
    }

    private static HTMLElement createBookingForm(HTMLSelectElement sessionSelect, HTMLElement sessionsList) {
        HTMLDocument document = HTMLDocument.current();
        HTMLElement form = document.createElement("div");

        updateSessionDropdown(sessionSelect);

        HTMLInputElement seatInput = (HTMLInputElement) document.createElement("input");
        seatInput.setPlaceholder("Номер места");

        HTMLElement button = createButton("Забронировать", () -> {
            String selectedSessionIdStr = sessionSelect.getValue();
            int seatNumber;
            try {
                seatNumber = Integer.parseInt(seatInput.getValue());
            } catch (NumberFormatException e) {
                Window.alert("Введите корректный номер места");
                return;
            }

            Long sessionId = Long.parseLong(selectedSessionIdStr);
            Session session = sessionViewModel.getSessionById(sessionId);

            if (session == null) {
                Window.alert("Сеанс не найден");
                return;
            }

            boolean booked = occupancyViewModel.bookSeat(session, seatNumber);
            if (booked) {
                Window.alert("Место успешно забронировано");
            } else {
                Window.alert("Не удалось забронировать место. Возможно, оно занято или номер некорректен.");
            }

            updateSessionsList(sessionsList);
        });

        form.appendChild(sessionSelect);
        form.appendChild(seatInput);
        form.appendChild(button);

        return form;
    }

    private static void updateMoviesList(HTMLElement list) {
        list.setInnerHTML("");
        for (Movie movie : movieViewModel.getMovies()) {
            HTMLElement li = HTMLDocument.current().createElement("li");

            long durationMinutes = movie.getDuration().toMinutes(); 

            li.appendChild(HTMLDocument.current().createTextNode(
                    "ID: " + movie.getId() +
                            " | " + movie.getTitle() +
                            " — " + movie.getAuthor() +
                            " — " + durationMinutes + " мин"
            ));

            list.appendChild(li);
        }
    }

    private static void updateHallsList(HTMLElement list) {
        list.setInnerHTML("");
        for (Hall hall : hallViewModel.getHalls()) {
            HTMLElement li = HTMLDocument.current().createElement("li");
            li.appendChild(HTMLDocument.current().createTextNode(
                    "Зал №" + hall.getNumber() + ", мест: " + hall.getSeatCount() + ", диаметр экрана (футы): " + hall.getScreenDiameterFeet() + ", 3D: " + (hall.isSupports3D() ? "да" : "нет")
            ));
            list.appendChild(li);
        }
    }

    private static void updateSessionsList(HTMLElement list) {
        list.setInnerHTML("");
        for (Session session : sessionViewModel.getSessions()) {
            HTMLElement li = HTMLDocument.current().createElement("li");

            LocalDateTime time = session.getTime();
            String date = time.toLocalDate().toString();
            String hourMinute = time.toLocalTime().withSecond(0).withNano(0).toString();

            li.appendChild(HTMLDocument.current().createTextNode(
                    "Сеанс ID: " + session.getId() +
                            " | Фильм: " + session.getMovie().getTitle() +
                            " | Зал: " + session.getHall().getNumber() +
                            " | Дата: " + date +
                            " | Время: " + hourMinute +
                            " | Цена: " + session.getPrice() +
                            " | Свободно мест: " + occupancyViewModel.getFreeSeatsCountForSession(session)
            ));
            list.appendChild(li);

            updateSessionDropdown(sessionSelect);
        }
    }

    private static HTMLElement createOccupiedSeatsButton() {
        return createButton("Показать занятые места", () -> {
            String selectedSessionIdStr = sessionSelect.getValue();
            if (selectedSessionIdStr == null || selectedSessionIdStr.isEmpty()) {
                Window.alert("Сначала выберите сеанс.");
                return;
            }

            Long sessionId = Long.parseLong(selectedSessionIdStr);
            Session session = sessionViewModel.getSessionById(sessionId);

            if (session == null) {
                Window.alert("Сеанс не найден.");
                return;
            }

            List<Integer> occupiedSeats = occupancyViewModel.getOccupiedSeatsForSession(session);
            if (occupiedSeats.isEmpty()) {
                Window.alert("Все места свободны.");
            } else {
                String seats = occupiedSeats.stream()
                        .map(String::valueOf)
                        .reduce((a, b) -> a + ", " + b)
                        .orElse("");
                Window.alert("Занятые места: " + seats);
            }
        });
    }

    private static void updateMovieSelect(HTMLSelectElement select) {
        select.setInnerHTML("");

        for (Movie movie : movieViewModel.getMovies()) {
            HTMLOptionElement option = (HTMLOptionElement) HTMLDocument.current().createElement("option");
            option.setValue(movie.getId().toString());
            option.appendChild(HTMLDocument.current().createTextNode(movie.getTitle()));
            select.appendChild(option);
        }
    }


}

