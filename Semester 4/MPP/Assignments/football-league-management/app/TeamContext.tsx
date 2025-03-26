"use client";

import React, { createContext, useContext, useState } from "react";

export interface Team {
  name: string;
  coachName: string;
  homeStadium: string;
  foundedYear: number;
  wins: number;
  draws: number;
  losses: number;
  goalsScored: number;
  goalsConceded: number;
  players: string[];
  country: string;
}

interface TeamsContextType {
  teams: Team[];
  setTeams: React.Dispatch<React.SetStateAction<Team[]>>;
}

const TeamsContext = createContext<TeamsContextType | undefined>(undefined);

export const TeamsProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [teams, setTeams] = useState<Team[]>([
    {
      name: "Arsenal",
      coachName: "Mikel Arteta",
      homeStadium: "Emirates Stadium",
      foundedYear: 1886,
      wins: 20,
      draws: 5,
      losses: 3,
      goalsScored: 60,
      goalsConceded: 25,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Aston Villa",
      coachName: "Unai Emery",
      homeStadium: "Villa Park",
      foundedYear: 1874,
      wins: 17,
      draws: 6,
      losses: 5,
      goalsScored: 55,
      goalsConceded: 30,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Bournemouth",
      coachName: "Andoni Iraola",
      homeStadium: "Vitality Stadium",
      foundedYear: 1899,
      wins: 10,
      draws: 9,
      losses: 10,
      goalsScored: 38,
      goalsConceded: 40,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Brentford",
      coachName: "Thomas Frank",
      homeStadium: "Gtech Community Stadium",
      foundedYear: 1889,
      wins: 9,
      draws: 7,
      losses: 12,
      goalsScored: 35,
      goalsConceded: 42,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Brighton",
      coachName: "Roberto De Zerbi",
      homeStadium: "Amex Stadium",
      foundedYear: 1901,
      wins: 12,
      draws: 8,
      losses: 8,
      goalsScored: 45,
      goalsConceded: 35,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Burnley",
      coachName: "Vincent Kompany",
      homeStadium: "Turf Moor",
      foundedYear: 1882,
      wins: 5,
      draws: 7,
      losses: 16,
      goalsScored: 27,
      goalsConceded: 50,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Chelsea",
      coachName: "Mauricio Pochettino",
      homeStadium: "Stamford Bridge",
      foundedYear: 1905,
      wins: 15,
      draws: 6,
      losses: 7,
      goalsScored: 50,
      goalsConceded: 35,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Crystal Palace",
      coachName: "Roy Hodgson",
      homeStadium: "Selhurst Park",
      foundedYear: 1905,
      wins: 8,
      draws: 9,
      losses: 11,
      goalsScored: 30,
      goalsConceded: 35,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Everton",
      coachName: "Sean Dyche",
      homeStadium: "Goodison Park",
      foundedYear: 1878,
      wins: 10,
      draws: 6,
      losses: 12,
      goalsScored: 32,
      goalsConceded: 38,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Fulham",
      coachName: "Marco Silva",
      homeStadium: "Craven Cottage",
      foundedYear: 1879,
      wins: 11,
      draws: 8,
      losses: 9,
      goalsScored: 36,
      goalsConceded: 37,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Liverpool",
      coachName: "Jürgen Klopp",
      homeStadium: "Anfield",
      foundedYear: 1892,
      wins: 18,
      draws: 7,
      losses: 3,
      goalsScored: 65,
      goalsConceded: 28,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Luton Town",
      coachName: "Rob Edwards",
      homeStadium: "Kenilworth Road",
      foundedYear: 1885,
      wins: 6,
      draws: 6,
      losses: 14,
      goalsScored: 28,
      goalsConceded: 45,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Manchester City",
      coachName: "Pep Guardiola",
      homeStadium: "Etihad Stadium",
      foundedYear: 1880,
      wins: 19,
      draws: 6,
      losses: 3,
      goalsScored: 70,
      goalsConceded: 30,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Manchester United",
      coachName: "Erik ten Hag",
      homeStadium: "Old Trafford",
      foundedYear: 1878,
      wins: 16,
      draws: 5,
      losses: 7,
      goalsScored: 48,
      goalsConceded: 34,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Newcastle United",
      coachName: "Eddie Howe",
      homeStadium: "St. James' Park",
      foundedYear: 1892,
      wins: 14,
      draws: 6,
      losses: 8,
      goalsScored: 47,
      goalsConceded: 32,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Nottingham Forest",
      coachName: "Nuno Espírito Santo",
      homeStadium: "City Ground",
      foundedYear: 1865,
      wins: 7,
      draws: 9,
      losses: 12,
      goalsScored: 30,
      goalsConceded: 40,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Sheffield United",
      coachName: "Chris Wilder",
      homeStadium: "Bramall Lane",
      foundedYear: 1889,
      wins: 4,
      draws: 5,
      losses: 19,
      goalsScored: 25,
      goalsConceded: 55,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Tottenham Hotspur",
      coachName: "Ange Postecoglou",
      homeStadium: "Tottenham Hotspur Stadium",
      foundedYear: 1882,
      wins: 16,
      draws: 5,
      losses: 7,
      goalsScored: 50,
      goalsConceded: 35,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "West Ham United",
      coachName: "David Moyes",
      homeStadium: "London Stadium",
      foundedYear: 1895,
      wins: 12,
      draws: 7,
      losses: 9,
      goalsScored: 38,
      goalsConceded: 36,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    },
    {
      name: "Wolverhampton Wanderers",
      coachName: "Gary O'Neil",
      homeStadium: "Molineux Stadium",
      foundedYear: 1877,
      wins: 10,
      draws: 8,
      losses: 10,
      goalsScored: 35,
      goalsConceded: 38,
      players: ["Player1", "Player2", "Player3"],
      country: "England",
    }
  ]);

  return (
    <TeamsContext.Provider value={{ teams, setTeams }}>
      {children}
    </TeamsContext.Provider>
  );
};

export const useTeams = (): TeamsContextType => {
  const context = useContext(TeamsContext);
  if (!context) {
    throw new Error("useTeams must be used within a TeamsProvider");
  }
  return context;
};