import {
    getTeams,
    addTeam,
    updateTeams,
    deleteTeam,
    calculatePositions
  } from "../data";

import { Team, RankedTeam } from "../data";

const baseTeam: Team = {
    name: "Test FC",
    coachName: "Test Coach",
    homeStadium: "Test Stadium",
    foundedYear: 2000,
    wins: 10,
    draws: 5,
    losses: 3,
    goalsScored: 30,
    goalsConceded: 20,
    players: ["Player 1", "Player 2"],
    country: "Testland",
};

beforeEach(() => {
    updateTeams([]);
});

test("calculatePositions returns teams with correct positions", () => {
    const ranked = calculatePositions([
      { ...baseTeam, name: "A", wins: 10, draws: 0, losses: 0, goalsScored: 30, goalsConceded: 10 },
      { ...baseTeam, name: "B", wins: 9, draws: 3, losses: 0, goalsScored: 25, goalsConceded: 10 },
      { ...baseTeam, name: "C", wins: 9, draws: 3, losses: 0, goalsScored: 20, goalsConceded: 8 },
    ]);
  
    expect(ranked[0].name).toBe("A");
    expect(ranked[1].name).toBe("B");
    expect(ranked[2].position).toBe(3);
});

test("addTeam adds a new team and recalculates positions", () => {
    addTeam(baseTeam);
    const teams = getTeams();
  
    expect(teams.length).toBe(1);
    expect(teams[0].name).toBe("Test FC");
});

test("addTeam does not add duplicate teams", () => {
    addTeam(baseTeam);
    addTeam(baseTeam);
    const teams = getTeams();
  
    expect(teams.length).toBe(1);
});

test("deleteTeam removes a team and recalculates", () => {
    addTeam(baseTeam);
    const deleted = deleteTeam("Test FC");
  
    expect(deleted).toBe(true);
    expect(getTeams().length).toBe(0);
});
  
test("deleteTeam returns false if team not found", () => {
    const deleted = deleteTeam("Nonexistent");
    expect(deleted).toBe(false);
});
  
test("calculatePositions sorts teams by points first", () => {
    const ranked = calculatePositions([
      { ...baseTeam, name: "Low Points", wins: 5, draws: 3, losses: 12, goalsScored: 40, goalsConceded: 10 }, // 18 pts
      { ...baseTeam, name: "High Points", wins: 15, draws: 2, losses: 3, goalsScored: 15, goalsConceded: 20 }, // 47 pts
      { ...baseTeam, name: "Medium Points", wins: 10, draws: 4, losses: 6, goalsScored: 30, goalsConceded: 15 }, // 34 pts
    ]);
  
    expect(ranked[0].name).toBe("High Points");
    expect(ranked[0].points).toBe(47);
    expect(ranked[1].name).toBe("Medium Points");
    expect(ranked[1].points).toBe(34);
    expect(ranked[2].name).toBe("Low Points");
    expect(ranked[2].points).toBe(18);
});
  