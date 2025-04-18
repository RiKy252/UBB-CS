import { NextResponse } from "next/server";
import { GET, POST } from "../route";
import { getTeams, addTeam, updateTeams } from "../data";

jest.mock("next/server", () => ({
  NextResponse: {
    json: jest.fn(() => ({
      mock: {
        calls: []
      }
    }))
  }
}));

jest.mock("../data", () => ({
  getTeams: jest.fn(),
  addTeam: jest.fn(),
  updateTeams: jest.fn()
}));

describe("GET route", () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  test("returns empty array with metadata when no teams exist", async () => {
    (getTeams as jest.Mock).mockReturnValue([]);
    
    await GET();
    
    expect(getTeams).toHaveBeenCalled();
    expect(NextResponse.json).toHaveBeenCalledWith([]);
  });

  test("calculates correct metadata for a single team", async () => {
    const mockTeam = {
      name: "Team A",
      wins: 10,
      draws: 5,
      losses: 3
    };
    
    (getTeams as jest.Mock).mockReturnValue([mockTeam]);
    
    await GET();
    
    expect(NextResponse.json).toHaveBeenCalledWith([{
      ...mockTeam,
      metadata: {
        isMostWins: true,
        isLeastWins: true,
        isAvgWins: true
      }
    }]);
  });

  test("calculates correct metadata for multiple teams with different wins", async () => {
    const mockTeams = [
      { name: "Team A", wins: 10, draws: 5, losses: 3 },
      { name: "Team B", wins: 15, draws: 2, losses: 1 },
      { name: "Team C", wins: 5, draws: 8, losses: 7 }
    ];
    
    (getTeams as jest.Mock).mockReturnValue(mockTeams);
    
    await GET();
    
    expect(NextResponse.json).toHaveBeenCalledWith([
      {
        ...mockTeams[0],
        metadata: {
          isMostWins: false,
          isLeastWins: false,
          isAvgWins: true 
        }
      },
      {
        ...mockTeams[1],
        metadata: {
          isMostWins: true,
          isLeastWins: false,
          isAvgWins: false
        }
      },
      {
        ...mockTeams[2],
        metadata: {
          isMostWins: false,
          isLeastWins: true,
          isAvgWins: false
        }
      }
    ]);
  });

  test("correctly handles teams with equal number of wins", async () => {
    const mockTeams = [
      { name: "Team A", wins: 10, draws: 5, losses: 3 },
      { name: "Team B", wins: 10, draws: 2, losses: 1 },
      { name: "Team C", wins: 5, draws: 8, losses: 7 }
    ];
    
    (getTeams as jest.Mock).mockReturnValue(mockTeams);
    
    await GET();
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    
    expect(result[0].metadata.isMostWins).toBe(true);
    expect(result[1].metadata.isMostWins).toBe(true);
    expect(result[2].metadata.isMostWins).toBe(false);
    
    expect(result[0].metadata.isLeastWins).toBe(false);
    expect(result[1].metadata.isLeastWins).toBe(false);
    expect(result[2].metadata.isLeastWins).toBe(true);
  });
});

describe("POST route", () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  test("returns 400 when required fields are missing", async () => {
    const mockTeam = {
      name: "Team A",
      homeStadium: "Stadium A",
      foundedYear: 2000,
      wins: 10
    };
    
    const request = new Request("http://localhost", {
      method: "POST",
      body: JSON.stringify(mockTeam),
      headers: { "Content-Type": "application/json" }
    });
    
    await POST(request);
    
    expect(NextResponse.json).toHaveBeenCalledWith(
      { error: "Name and coach name are required" },
      { status: 400 }
    );
  });

  test("returns 400 when name is missing", async () => {
    const mockTeam = {
      coachName: "Coach A",
      homeStadium: "Stadium A"
    };
    
    const request = new Request("http://localhost", {
      method: "POST",
      body: JSON.stringify(mockTeam),
      headers: { "Content-Type": "application/json" }
    });
    
    await POST(request);
    
    expect(NextResponse.json).toHaveBeenCalledWith(
      { error: "Name and coach name are required" },
      { status: 400 }
    );
  });

  test("returns 400 when data is invalid", async () => {
    const request = new Request("http://localhost", {
      method: "POST",
      body: JSON.stringify({}),
      headers: { "Content-Type": "application/json" }
    });

    jest.spyOn(request, "json").mockRejectedValue(new Error("Invalid JSON"));
    
    await POST(request);
    
    expect(NextResponse.json).toHaveBeenCalledWith(
      { error: "Invalid data" },
      { status: 400 }
    );
  });

  test("handles all team fields correctly", async () => {
    const mockTeam = {
      name: "Team A",
      coachName: "Coach A",
      homeStadium: "Stadium A",
      foundedYear: 2000,
      wins: 10,
      draws: 5,
      losses: 3,
      goalsScored: 30,
      goalsConceded: 15,
      players: ["Player 1", "Player 2"],
      country: "Country A"
    };
    
    (addTeam as jest.Mock).mockReturnValue([mockTeam]);
    
    const request = new Request("http://localhost", {
      method: "POST",
      body: JSON.stringify(mockTeam),
      headers: { "Content-Type": "application/json" }
    });

    jest.spyOn(request, "json").mockResolvedValue(mockTeam);
    
    await POST(request);
    
    expect(addTeam).toHaveBeenCalledWith({
      name: "Team A",
      coachName: "Coach A",
      homeStadium: "Stadium A",
      foundedYear: 2000,
      wins: 10,
      draws: 5,
      losses: 3,
      goalsScored: 30,
      goalsConceded: 15,
      players: ["Player 1", "Player 2"],
      country: "Country A"
    });
  });
});