"use client";

import React, { createContext, useContext, useEffect, useState } from "react";
import { faker } from "@faker-js/faker";

const generateFakeTeams = (count: number): Team[] => {
  return Array.from({ length: count }, () => ({
    name: faker.company.name(),
    coachName: faker.name.fullName(),
    homeStadium: faker.company.name() + " Stadium",
    foundedYear: faker.number.int({ min: 1850, max: 2023 }),
    wins: faker.number.int({ min: 0, max: 20 }),
    draws: faker.number.int({ min: 0, max: 10 }),
    losses: faker.number.int({ min: 0, max: 20 }),
    goalsScored: faker.number.int({ min: 10, max: 80 }),
    goalsConceded: faker.number.int({ min: 10, max: 80 }),
    players: Array.from({ length: 11 }, () => faker.name.fullName()),
    country: faker.address.country(),
  }));
};

// Define initial Premier League teams (20 teams)
const premierLeagueTeams: Team[] = [
  { name: "Arsenal", coachName: "Mikel Arteta", homeStadium: "Emirates Stadium", foundedYear: 1886, wins: 18, draws: 6, losses: 4, goalsScored: 60, goalsConceded: 30, players: [], country: "England" },
  { name: "Aston Villa", coachName: "Unai Emery", homeStadium: "Villa Park", foundedYear: 1874, wins: 16, draws: 5, losses: 7, goalsScored: 55, goalsConceded: 35, players: [], country: "England" },
  { name: "Bournemouth", coachName: "Andoni Iraola", homeStadium: "Vitality Stadium", foundedYear: 1899, wins: 8, draws: 6, losses: 14, goalsScored: 35, goalsConceded: 45, players: [], country: "England" },
  { name: "Brentford", coachName: "Thomas Frank", homeStadium: "Gtech Community Stadium", foundedYear: 1889, wins: 12, draws: 9, losses: 7, goalsScored: 40, goalsConceded: 39, players: [], country: "England" },
  { name: "Brighton & Hove Albion", coachName: "Roberto De Zerbi", homeStadium: "Amex Stadium", foundedYear: 1901, wins: 15, draws: 7, losses: 6, goalsScored: 50, goalsConceded: 35, players: [], country: "England" },
  { name: "Chelsea", coachName: "Graham Potter", homeStadium: "Stamford Bridge", foundedYear: 1905, wins: 10, draws: 5, losses: 12, goalsScored: 45, goalsConceded: 40, players: [], country: "England" },
  { name: "Crystal Palace", coachName: "Patrick Vieira", homeStadium: "Selhurst Park", foundedYear: 1905, wins: 9, draws: 8, losses: 11, goalsScored: 38, goalsConceded: 42, players: [], country: "England" },
  { name: "Everton", coachName: "Frank Lampard", homeStadium: "Goodison Park", foundedYear: 1878, wins: 7, draws: 5, losses: 15, goalsScored: 30, goalsConceded: 50, players: [], country: "England" },
  { name: "Fulham", coachName: "Marco Silva", homeStadium: "Craven Cottage", foundedYear: 1879, wins: 12, draws: 6, losses: 8, goalsScored: 48, goalsConceded: 41, players: [], country: "England" },
  { name: "Leeds United", coachName: "Jesse Marsch", homeStadium: "Elland Road", foundedYear: 1919, wins: 9, draws: 4, losses: 13, goalsScored: 38, goalsConceded: 48, players: [], country: "England" },
  { name: "Leicester City", coachName: "Brendan Rodgers", homeStadium: "King Power Stadium", foundedYear: 1884, wins: 11, draws: 7, losses: 10, goalsScored: 46, goalsConceded: 45, players: [], country: "England" },
  { name: "Liverpool", coachName: "Jürgen Klopp", homeStadium: "Anfield", foundedYear: 1892, wins: 17, draws: 6, losses: 5, goalsScored: 65, goalsConceded: 30, players: [], country: "England" },
  { name: "Manchester City", coachName: "Pep Guardiola", homeStadium: "Etihad Stadium", foundedYear: 1880, wins: 20, draws: 4, losses: 2, goalsScored: 80, goalsConceded: 25, players: [], country: "England" },
  { name: "Manchester United", coachName: "Erik ten Hag", homeStadium: "Old Trafford", foundedYear: 1878, wins: 15, draws: 5, losses: 6, goalsScored: 60, goalsConceded: 35, players: [], country: "England" },
  { name: "Newcastle United", coachName: "Eddie Howe", homeStadium: "St James' Park", foundedYear: 1892, wins: 14, draws: 7, losses: 5, goalsScored: 55, goalsConceded: 32, players: [], country: "England" },
  { name: "Nottingham Forest", coachName: "Steve Cooper", homeStadium: "City Ground", foundedYear: 1865, wins: 10, draws: 8, losses: 10, goalsScored: 40, goalsConceded: 45, players: [], country: "England" },
  { name: "Southampton", coachName: "Ralph Hasenhüttl", homeStadium: "St Mary's Stadium", foundedYear: 1885, wins: 6, draws: 5, losses: 15, goalsScored: 35, goalsConceded: 50, players: [], country: "England" },
  { name: "Tottenham Hotspur", coachName: "Antonio Conte", homeStadium: "Tottenham Hotspur Stadium", foundedYear: 1882, wins: 16, draws: 5, losses: 7, goalsScored: 60, goalsConceded: 40, players: [], country: "England" },
  { name: "West Ham United", coachName: "David Moyes", homeStadium: "London Stadium", foundedYear: 1895, wins: 8, draws: 6, losses: 12, goalsScored: 35, goalsConceded: 45, players: [], country: "England" },
  { name: "Wolverhampton Wanderers", coachName: "Bruno Lage", homeStadium: "Molineux Stadium", foundedYear: 1877, wins: 10, draws: 5, losses: 13, goalsScored: 40, goalsConceded: 40, players: [], country: "England" },
];

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
  addMoreFakeTeams: () => void;
}

const TeamsContext = createContext<TeamsContextType | undefined>(undefined);

export const TeamsProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [teams, setTeams] = useState<Team[]>(premierLeagueTeams);

  const addMoreFakeTeams = () => {
    const newTeams = generateFakeTeams(50); // Generate 50 new fake teams
    setTeams([...teams, ...newTeams]); // Append them to the current teams
  };

  return (
    <TeamsContext.Provider value={{ teams, setTeams, addMoreFakeTeams }}>
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