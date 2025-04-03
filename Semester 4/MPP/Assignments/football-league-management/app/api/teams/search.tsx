import { NextResponse } from "next/server";
import { teams } from "./data";

export async function GET(req: Request) {
  const { searchParams } = new URL(req.url);

  // Get the search query (team name)
  const query = searchParams.get("query");
  
  if (!query) {
    return NextResponse.json(teams); // Return all teams if no search term
  }

  // Filter teams by name (case-insensitive)
  const filteredTeams = teams.filter((team) =>
    team.name.toLowerCase().includes(query.toLowerCase())
  );

  return NextResponse.json(filteredTeams);
}
