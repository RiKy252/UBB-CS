import { NextResponse } from "next/server";
import { GET } from "../sort/route";
import { getTeams } from "../data";

jest.mock("next/server", () => ({
  NextResponse: {
    json: jest.fn((data) => ({ data }))
  }
}));

jest.mock("../data", () => ({
  getTeams: jest.fn()
}));

function createRequest(url: string): Request {
    return new Request(url) as Request;
}

describe("GET search and sort route", () => {
  const mockTeams = [
    { name: "Arsenal", wins: 20, draws: 5, losses: 3, points: 65, goalsScored: 60, goalsConceded: 25 },
    { name: "Chelsea", wins: 15, draws: 8, losses: 7, points: 53, goalsScored: 50, goalsConceded: 30 },
    { name: "Liverpool", wins: 18, draws: 4, losses: 8, points: 58, goalsScored: 55, goalsConceded: 35 },
    { name: "Manchester City", wins: 22, draws: 4, losses: 4, points: 70, goalsScored: 70, goalsConceded: 20 },
    { name: "Manchester United", wins: 16, draws: 6, losses: 8, points: 54, goalsScored: 45, goalsConceded: 40 }
  ];

  beforeEach(() => {
    jest.clearAllMocks();
    (getTeams as jest.Mock).mockReturnValue([...mockTeams]);
  });

  test("returns all teams sorted by points (default) when no params", async () => {
    const request = createRequest("https://example.com/api/teams");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester City"); 
    expect(result[1].name).toBe("Arsenal");
    expect(result[4].name).toBe("Chelsea"); 
  });

  test("filters teams by query parameter", async () => {
    const request = createRequest("https://example.com/api/teams?query=man");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result.length).toBe(2);
    expect(result[0].name).toBe("Manchester City");
    expect(result[1].name).toBe("Manchester United");
  });

  test("sorts teams by name in ascending order", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=name&order=asc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Arsenal");
    expect(result[1].name).toBe("Chelsea");
    expect(result[2].name).toBe("Liverpool");
    expect(result[3].name).toBe("Manchester City");
    expect(result[4].name).toBe("Manchester United");
  });

  test("sorts teams by name in descending order", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=name&order=desc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester United");
    expect(result[1].name).toBe("Manchester City");
    expect(result[2].name).toBe("Liverpool");
    expect(result[3].name).toBe("Chelsea");
    expect(result[4].name).toBe("Arsenal");
  });

  test("sorts teams by wins in ascending order", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=wins&order=asc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Chelsea"); 
    expect(result[4].name).toBe("Manchester City"); 
  });

  test("sorts teams by wins in descending order", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=wins&order=desc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester City"); 
    expect(result[4].name).toBe("Chelsea");
  });

  test("sorts teams by goalsScored", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=goalsScored");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester City"); 
    expect(result[4].name).toBe("Manchester United");
  });

  test("sorts teams by goalsConceded", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=goalsConceded&order=asc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester City");
    expect(result[4].name).toBe("Manchester United");
  });

  test("handles unknown sortBy parameter by defaulting to name", async () => {
    const request = createRequest("https://example.com/api/teams?sortBy=unknown");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result[0].name).toBe("Manchester United");
    expect(result[1].name).toBe("Manchester City");
  });

  test("computes metadata correctly", async () => {
    const request = createRequest("https://example.com/api/teams");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    
    expect(result.find((t: { name: string; }) => t.name === "Manchester City").metadata.isMostWins).toBe(true);
    
    expect(result.find((t: { name: string; }) => t.name === "Chelsea").metadata.isLeastWins).toBe(true);
    
    expect(result.find((t: { name: string; }) => t.name === "Liverpool").metadata.isAvgWins).toBe(true);
    
    expect(result.find((t: { name: string; }) => t.name === "Manchester United").metadata.isAvgWins).toBe(false);
  });

  test("handles empty teams array", async () => {
    (getTeams as jest.Mock).mockReturnValue([]);
    
    const request = createRequest("https://example.com/api/teams");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result).toEqual([]);
  });

  test("handles case-insensitive queries", async () => {
    const request = createRequest("https://example.com/api/teams?query=ARSENAL");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result.length).toBe(1);
    expect(result[0].name).toBe("Arsenal");
  });

  test("returns empty array when no matches for query", async () => {
    const request = createRequest("https://example.com/api/teams?query=nonexistent");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result).toEqual([]);
  });

  test("combines search and sort functionality", async () => {
    const request = createRequest("https://example.com/api/teams?query=man&sortBy=goalsScored&order=asc");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result.length).toBe(2);
    expect(result[0].name).toBe("Manchester United"); 
    expect(result[1].name).toBe("Manchester City"); 
  });

  test("handles teams with identical sort values", async () => {
    const mockTeamsWithTie = [
      { name: "Arsenal", wins: 20, points: 65, goalsScored: 60, goalsConceded: 25 },
      { name: "Chelsea", wins: 20, points: 65, goalsScored: 50, goalsConceded: 30 }
    ];
    
    (getTeams as jest.Mock).mockReturnValue(mockTeamsWithTie);
    
    const request = createRequest("https://example.com/api/teams?sortBy=wins");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result.length).toBe(2);
    
    expect(result[0].metadata.isMostWins).toBe(true);
    expect(result[1].metadata.isMostWins).toBe(true);
  });

  test("calculates metadata with single team", async () => {
    (getTeams as jest.Mock).mockReturnValue([mockTeams[0]]);
    
    const request = createRequest("https://example.com/api/teams");
    
    await GET(request);
    
    const result = (NextResponse.json as jest.Mock).mock.calls[0][0];
    expect(result.length).toBe(1);
    expect(result[0].metadata.isMostWins).toBe(true);
    expect(result[0].metadata.isLeastWins).toBe(true);
    expect(result[0].metadata.isAvgWins).toBe(true);
  });
});