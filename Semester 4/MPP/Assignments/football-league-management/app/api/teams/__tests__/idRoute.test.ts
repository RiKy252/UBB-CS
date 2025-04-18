import { NextResponse } from "next/server";
import { GET, DELETE, PATCH } from "../[id]/route";
import { calculatePositions, getTeams, updateTeams, deleteTeam, Team } from "../data";

jest.mock("next/server", () => ({
  NextResponse: {
    json: jest.fn((data, options) => ({ data, options }))
  }
}));

jest.mock("../data", () => ({
  getTeams: jest.fn(),
  updateTeams: jest.fn(),
  deleteTeam: jest.fn(),
  calculatePositions: jest.fn((teams) => teams)
}));

function createRequest(url: string, method: string = 'GET', body?: any): Request {
  const options: RequestInit = { method };
  if (body) {
    options.body = JSON.stringify(body);
    options.headers = { 'Content-Type': 'application/json' };
  }
  return new Request(url, options) as Request;
}

describe("Team ID Routes", () => {
  const mockTeams = [
    { name: "Arsenal", wins: 20, draws: 5, losses: 3, goalsScored: 60, goalsConceded: 25 },
    { name: "Chelsea", wins: 15, draws: 8, losses: 7, goalsScored: 50, goalsConceded: 30 },
    { name: "Liverpool", wins: 18, draws: 4, losses: 8, goalsScored: 55, goalsConceded: 35 },
  ] as Team[];

  beforeEach(() => {
    jest.clearAllMocks();
    (getTeams as jest.Mock).mockReturnValue([...mockTeams]);
    (calculatePositions as jest.Mock).mockImplementation((teams) => teams);
    (updateTeams as jest.Mock).mockImplementation(() => true);
    (deleteTeam as jest.Mock).mockImplementation(() => true);
  });

  describe("GET", () => {
    test("returns a team when found", async () => {
      const request = createRequest("https://example.com/api/teams/Arsenal");
      const params = { id: "Arsenal" };
      
      await GET(request, { params });
      
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      expect(result).toEqual(mockTeams[0]);
    });

    test("returns 404 when team is not found", async () => {
      const request = createRequest("https://example.com/api/teams/NonExistent");
      const params = { id: "NonExistent" };
      
      await GET(request, { params });
      
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      const options = (NextResponse.json as jest.Mock).mock.calls[0][1];
      
      expect(result).toEqual({ error: "Team not found" });
      expect(options).toEqual({ status: 404 });
    });
  });

  describe("DELETE", () => {
    test("deletes a team successfully", async () => {
      const request = createRequest("https://example.com/api/teams/Arsenal", "DELETE");
      const params = { id: "Arsenal" };
      
      await DELETE(request, { params });
      
      expect(deleteTeam).toHaveBeenCalledWith("Arsenal");
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      expect(result).toEqual({ message: "Team deleted successfully" });
    });

    test("returns 404 when team to delete is not found", async () => {
      (deleteTeam as jest.Mock).mockReturnValue(false);
      
      const request = createRequest("https://example.com/api/teams/NonExistent", "DELETE");
      const params = { id: "NonExistent" };
      
      await DELETE(request, { params });
      
      expect(deleteTeam).toHaveBeenCalledWith("NonExistent");
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      const options = (NextResponse.json as jest.Mock).mock.calls[0][1];
      
      expect(result).toEqual({ error: "Team not found" });
      expect(options).toEqual({ status: 404 });
    });

    test("handles URL encoded team names", async () => {
      const request = createRequest("https://example.com/api/teams/Manchester%20United", "DELETE");
      const params = { id: "Manchester%20United" };
      
      await DELETE(request, { params });
      
      expect(deleteTeam).toHaveBeenCalledWith("Manchester United");
    });
  });

  describe("PATCH", () => {
    test("updates a team successfully", async () => {
      const updatedData = { wins: 21, points: 68 };
      const request = createRequest(
        "https://example.com/api/teams/Arsenal", 
        "PATCH", 
        updatedData
      );
      const params = { id: "Arsenal" };
      
      await PATCH(request, { params });
      
      expect(getTeams).toHaveBeenCalled();
      expect(calculatePositions).toHaveBeenCalled();
      expect(updateTeams).toHaveBeenCalled();
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      expect(result).toEqual({
        ...mockTeams[0],
        ...updatedData
      });
    });

    test("returns 404 when team to update is not found", async () => {
      const updatedData = { wins: 21, points: 68 };
      const request = createRequest(
        "https://example.com/api/teams/NonExistent", 
        "PATCH", 
        updatedData
      );
      const params = { id: "NonExistent" };
      
      await PATCH(request, { params });
      
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      const options = (NextResponse.json as jest.Mock).mock.calls[0][1];
      
      expect(result).toEqual({ error: "Team not found" });
      expect(options).toEqual({ status: 404 });
    });

    test("handles invalid JSON data", async () => {
      const request = createRequest("https://example.com/api/teams/Arsenal", "PATCH");
      Object.defineProperty(request, 'json', {
        value: jest.fn().mockRejectedValue(new Error("Invalid JSON"))
      });
      
      const params = { id: "Arsenal" };
      
      await PATCH(request, { params });
      
      expect(NextResponse.json).toHaveBeenCalledTimes(1);
      const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
      const options = (NextResponse.json as jest.Mock).mock.calls[0][1];
      
      expect(result).toEqual({ error: "Invalid data" });
      expect(options).toEqual({ status: 400 });
    });

    test("handles URL encoded team names", async () => {
      const updatedData = { wins: 19, points: 63 };
      (getTeams as jest.Mock).mockReturnValue([
        ...mockTeams,
        { name: "Manchester United", wins: 16, points: 54 }
      ]);
      
      const request = createRequest(
        "https://example.com/api/teams/Manchester%20United", 
        "PATCH", 
        updatedData
      );
      const params = { id: "Manchester%20United" };
      
      await PATCH(request, { params });
      
      const updatedTeams = (updateTeams as jest.Mock).mock.calls[0][0];
      const updatedTeam = updatedTeams.find((t: Team) => t.name === "Manchester United");
      
      expect(updatedTeam).toBeDefined();
      expect(updatedTeam.wins).toBe(19);
      expect(updatedTeam.points).toBe(63);
    });

    test("calculates positions after updating", async () => {
      const updatedData = { wins: 21, points: 68 };
      const request = createRequest(
        "https://example.com/api/teams/Arsenal", 
        "PATCH", 
        updatedData
      );
      const params = { id: "Arsenal" };
      
      await PATCH(request, { params });
      
      const teamsPassedToCalculate = (calculatePositions as jest.Mock).mock.calls[0][0];
      expect(teamsPassedToCalculate[0].wins).toBe(21);
      expect(teamsPassedToCalculate[0].points).toBe(68);
      
      expect(updateTeams).toHaveBeenCalled();
    });
  });
});