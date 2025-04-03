import { NextResponse } from "next/server";
import { Team, teams, updateTeams } from "./data"

export async function GET() {
  return NextResponse.json(teams);
}

export async function POST(req: Request) {
  try {
    const { name, coachName, homeStadium, foundedYear, wins, draws, losses, goalsScored, goalsConceded, players, country } = await req.json();
    
    if (!name || !coachName) {
      return NextResponse.json({ error: "Name and coach name are required" }, { status: 400 });
    }

    const newTeam: Team = {
      id: String(teams.length + 1),
      name,
      coachName,
      homeStadium,
      foundedYear,
      wins: wins || 0,
      draws: draws || 0,
      losses: losses || 0,
      goalsScored: goalsScored || 0,
      goalsConceded: goalsConceded || 0,
      players: players || [],
      country: country || "Unknown",
    };

    updateTeams([...teams, newTeam]); 
    return NextResponse.json(newTeam, { status: 201 });

  } catch (error) {
    return NextResponse.json({ error: "Invalid data" }, { status: 400 });
  }
}
