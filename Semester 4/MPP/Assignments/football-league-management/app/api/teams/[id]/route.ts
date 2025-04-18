import { NextResponse } from "next/server";
import { calculatePositions, Team, getTeams, updateTeams, deleteTeam } from "../data";

export async function GET(req: Request, { params }: { params: { id: string } }) {
    const teams = getTeams(); // Fetch the teams from the data source
    const team = teams.find((t) => t.name === params.id);
    if (!team) {
      return NextResponse.json({ error: "Team not found" }, { status: 404 });
    }
    return NextResponse.json(team);
  }
  
  export async function DELETE(req: Request, { params }: { params: { id: string } }) {
    const teamName = decodeURIComponent(params.id);
    
    // Call deleteTeam with the team name
    const success = deleteTeam(teamName);
  
    if (!success) {
      return NextResponse.json({ error: "Team not found" }, { status: 404 });
    }
    
    return NextResponse.json({ message: "Team deleted successfully" });
  }
  
export async function PATCH(req: Request, { params }: { params: { id: string } }) {
  try {
    const waitParams = await params;
    const teamId = await waitParams.id;
    const teams = getTeams(); // Fetch the teams from the data source
    const teamName = decodeURIComponent(params.id);
    const teamIndex = teams.findIndex((t) => t.name === teamName);
    
    if (teamIndex === -1) {
      return NextResponse.json({ error: "Team not found" }, { status: 404 });
    }

    const updatedData = await req.json();
    teams[teamIndex] = { ...teams[teamIndex], ...updatedData };

    const updatedTeams = calculatePositions(teams);
    updateTeams(updatedTeams);
    return NextResponse.json(teams[teamIndex]);
  } catch (error) {
    return NextResponse.json({ error: "Invalid data" }, { status: 400 });
  }
}
