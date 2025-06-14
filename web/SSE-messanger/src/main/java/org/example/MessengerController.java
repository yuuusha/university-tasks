package org.example;

import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;
import java.io.IOException;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

@RestController
public class MessengerController {
    private final Map<String, List<SseEmitter>> roomEmitters = new ConcurrentHashMap<>();
    private final Map<String, List<Message>> roomMessages = new ConcurrentHashMap<>();

    @GetMapping(value = "/subscribe", produces = MediaType.TEXT_EVENT_STREAM_VALUE)
    public SseEmitter subscribe(@RequestParam(name = "room") String room) {
        SseEmitter emitter = new SseEmitter(60_000L);

        roomEmitters.computeIfAbsent(room, k -> new CopyOnWriteArrayList<>()).add(emitter);

        emitter.onCompletion(() -> roomEmitters.get(room).remove(emitter));
        emitter.onTimeout(() -> roomEmitters.get(room).remove(emitter));

        try {
            emitter.send(SseEmitter.event().data("connected"));
        } catch (IOException e) {
            emitter.complete();
        }

        return emitter;
    }


    @PostMapping("/send")
    public void sendMessage(@RequestBody Message message) {
        roomMessages.computeIfAbsent(message.getRoom(), k -> new CopyOnWriteArrayList<>()).add(message);

        List<SseEmitter> emitters = roomEmitters.getOrDefault(message.getRoom(), Collections.emptyList());
        List<SseEmitter> deadEmitters = new CopyOnWriteArrayList<>();

        for (SseEmitter emitter : emitters) {
            try {
                emitter.send(SseEmitter.event().data(message));
            } catch (IOException e) {
                emitter.complete();
                deadEmitters.add(emitter);
            }
        }
        emitters.removeAll(deadEmitters);
    }


    @GetMapping("/history")
    public List<Message> getHistory(@RequestParam(name = "room") String room) {
        return roomMessages.getOrDefault(room, Collections.emptyList());
    }
}
