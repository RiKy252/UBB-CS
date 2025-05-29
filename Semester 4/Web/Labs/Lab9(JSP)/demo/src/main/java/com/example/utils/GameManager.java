package com.example.utils;

import java.util.HashSet;
import java.util.Set;

public class GameManager {
    private static final Set<String> players = new HashSet<>();

    public static synchronized boolean join(String user) {
        if (players.contains(user)) return true;
        if (players.size() < 2) {
            players.add(user);
            return true;
        }
        return false;
    }

    public static synchronized void leave(String user) {
        players.remove(user);
    }
}