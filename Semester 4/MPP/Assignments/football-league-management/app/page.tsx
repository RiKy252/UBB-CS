"use client";

import React, { useState } from "react";
import { useRouter } from "next/navigation";
import { useTeams } from "./TeamContext";

export default function PremierLeagueTeams() {
  const { teams, setTeams } = useTeams();

  const calculatePositions = (teams: any[]) => {
    return teams
      .sort((a, b) => {
        const aPoints = a.wins * 3 + a.draws;
        const bPoints = b.wins * 3 + b.draws;
        if (bPoints !== aPoints) return bPoints - aPoints; // First leaderboard criteria: Points
        if (b.goalsScored !== a.goalsScored) return b.goalsScored - a.goalsScored; // Second leaderboard criteria: Goals scored
        return a.goalsConceded - b.goalsConceded; // Third leaderboard criteria: Goals conceded (less is better)
      })
      .map((team, index) => ({
        ...team,
        position: index + 1, // Assign position based on sorted order
      }));
  };

  if (!teams || teams.length === 0) {
    return (
      <div className="bg-black text-white min-h-screen flex items-center justify-center">
        <h1 className="text-3xl font-bold">No Teams Available</h1>
      </div>
    );
  }

  const winsArray = teams.map((team) => team.wins);
  const maxWins = Math.max(...winsArray);
  const minWins = Math.min(...winsArray);
  const avgWins = winsArray.reduce((sum, wins) => sum + wins, 0) / winsArray.length;

  const [sortedTeams, setSortedTeams] = useState(calculatePositions(teams));
  const [sortCriteria, setSortCriteria] = useState("points"); // Default sorting by points
  const [sortOrder, setSortOrder] = useState<"asc" | "desc">("desc"); // Default descending order
  const [searchQuery, setSearchQuery] = useState("");
  const [selectedTeams, setSelectedTeams] = useState<string[]>([]); // Track selected teams for deletion
  const [isModalOpen, setIsModalOpen] = useState(false); // Modal state
  const [newTeam, setNewTeam] = useState({
    name: "",
    coachName: "",
    homeStadium: "",
    foundedYear: "",
    wins: "",
    draws: "",
    losses: "",
    goalsScored: "",
    goalsConceded: "",
    players: "",
    country: "",
  });

  const [currentPage, setCurrentPage] = useState(1);
  const teamsPerPage = 10; 

  const getSortedTeams = () => {
    const filteredTeams = teams.filter((team) =>
      team.name.toLowerCase().includes(searchQuery.toLowerCase())
    );

    return [...filteredTeams].sort((a, b) => {
      let comparison = 0;

      if (sortCriteria === "points") {
        const aPoints = a.wins * 3 + a.draws;
        const bPoints = b.wins * 3 + b.draws;
        comparison = bPoints - aPoints;
      } else if (sortCriteria === "wins") {
        comparison = b.wins - a.wins;
      } else if (sortCriteria === "goalsScored") {
        comparison = b.goalsScored - a.goalsScored;
      } else if (sortCriteria === "goalsConceded") {
        comparison = b.goalsConceded - a.goalsConceded; // Less is better
      } else if (sortCriteria === "name") {
        comparison = b.name.localeCompare(a.name);
      }

      return sortOrder === "asc" ? -comparison : comparison;
    });
  };

  const paginatedTeams = getSortedTeams().slice(
    (currentPage - 1) * teamsPerPage,
    currentPage * teamsPerPage
  );

  const totalPages = Math.ceil(getSortedTeams().length / teamsPerPage);

  const handlePageChange = (newPage: number) => {
    if (newPage >= 1 && newPage <= totalPages) {
      setCurrentPage(newPage);
    }
  };

  const handleSortChange = (criteria: string) => {
    setSortCriteria(criteria);
  };

  const toggleSortOrder = () => {
    setSortOrder((prev) => (prev === "asc" ? "desc" : "asc"));
  };

  const handleSearch = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSearchQuery(event.target.value);
  };

  const handleCheckboxChange = (teamName: string) => {
    setSelectedTeams((prev) =>
      prev.includes(teamName)
        ? prev.filter((name) => name !== teamName) // Remove if already selected
        : [...prev, teamName] // Add if not selected
    );
  };

  const handleRemoveTeams = () => {
    if (selectedTeams.length === 0) {
      alert("Please select at least one team to remove.");
      return;
    }

    // Remove the selected teams
    const updatedTeams = teams.filter((team) => !selectedTeams.includes(team.name));
    setTeams(updatedTeams);
    setSortedTeams(calculatePositions(updatedTeams));
    setSelectedTeams([]); // Reset selected teams
  };

  const handleAddTeam = () => {
    setIsModalOpen(true); // Open the modal
  };

  const handleCloseModal = () => {
    setIsModalOpen(false); // Close the modal
    setNewTeam({
      name: "",
      coachName: "",
      homeStadium: "",
      foundedYear: "",
      wins: "",
      draws: "",
      losses: "",
      goalsScored: "",
      goalsConceded: "",
      players: "",
      country: "",
    });
  };

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;
    setNewTeam((prev) => ({ ...prev, [name]: value }));
  };

  const handleSaveTeam = () => {
    // Validate inputs
    if (!newTeam.name.trim()) {
      alert("Team Name cannot be empty.");
      return;
    }
    if (teams.some((team) => team.name.toLowerCase() === newTeam.name.toLowerCase())) {
      alert("Team Name must be unique.");
      return;
    }
    if (!newTeam.coachName.trim()) {
      alert("Coach Name cannot be empty.");
      return;
    }
    if (!newTeam.homeStadium.trim()) {
      alert("Home Stadium cannot be empty.");
      return;
    }
    if (!newTeam.country.trim()) {
      alert("Country cannot be empty.");
      return;
    }
    if (!newTeam.foundedYear || isNaN(Number(newTeam.foundedYear)) || Number(newTeam.foundedYear) <= 0) {
      alert("Founded Year must be a valid positive number.");
      return;
    }
    if (!newTeam.wins || isNaN(Number(newTeam.wins)) || Number(newTeam.wins) < 0) {
      alert("Wins must be a valid non-negative number.");
      return;
    }
    if (!newTeam.draws || isNaN(Number(newTeam.draws)) || Number(newTeam.draws) < 0) {
      alert("Draws must be a valid non-negative number.");
      return;
    }
    if (!newTeam.losses || isNaN(Number(newTeam.losses)) || Number(newTeam.losses) < 0) {
      alert("Losses must be a valid non-negative number.");
      return;
    }
    if (!newTeam.goalsScored || isNaN(Number(newTeam.goalsScored)) || Number(newTeam.goalsScored) < 0) {
      alert("Goals Scored must be a valid non-negative number.");
      return;
    }
    if (!newTeam.goalsConceded || isNaN(Number(newTeam.goalsConceded)) || Number(newTeam.goalsConceded) < 0) {
      alert("Goals Conceded must be a valid non-negative number.");
      return;
    }
    if (!newTeam.players.trim()) {
      alert("Players cannot be empty. Please separate player names with commas.");
      return;
    }

    // Create the new team object
    const team = {
      name: newTeam.name,
      coachName: newTeam.coachName,
      homeStadium: newTeam.homeStadium,
      foundedYear: parseInt(newTeam.foundedYear, 10),
      wins: parseInt(newTeam.wins, 10),
      draws: parseInt(newTeam.draws, 10),
      losses: parseInt(newTeam.losses, 10),
      goalsScored: parseInt(newTeam.goalsScored, 10),
      goalsConceded: parseInt(newTeam.goalsConceded, 10),
      players: newTeam.players.split(",").map((player) => player.trim()),
      country: newTeam.country,
    };

    // Add the new team and recalculate positions
    setTeams((prev) => [...prev, team]);
    const updatedTeams = calculatePositions([...teams, team]);
    setSortedTeams(updatedTeams);

    handleCloseModal(); // Close the modal
  };

  const router = useRouter();

  return (
    <div className="bg-black text-white min-h-screen p-4">
      <div className="container mx-auto bg-[#1d1d1d] text-gray-200 p-6 rounded-lg shadow-lg">
        <h2 className="text-2xl font-bold mb-4">Premier League Standings</h2>
        <div className="flex justify-between mb-4">
          <div className="flex gap-4">
            <input
              type="text"
              placeholder="Search teams..."
              value={searchQuery}
              onChange={handleSearch}
              className="p-2 rounded bg-gray-800 text-white border border-gray-600 w-150"
            />
            <button
              className="bg-green-500 text-white text-center p-2 rounded cursor-pointer w-30"
              onClick={handleAddTeam}
            >
              Add Team
            </button>
            <button
              className="bg-red-500 text-white text-center p-2 rounded cursor-pointer w-30"
              onClick={handleRemoveTeams}
            >
              Remove team
            </button>
            <div className="relative">
              <select
                value={sortCriteria}
                onChange={(e) => handleSortChange(e.target.value)}
                className="p-2 rounded bg-gray-800 text-white border border-gray-600"
              >
                <option value="points">Points</option>
                <option value="wins">Wins</option>
                <option value="goalsScored">Goals Scored</option>
                <option value="goalsConceded">Goals Conceded</option>
                <option value="name">Name</option>
              </select>
            </div>
            <button
              onClick={toggleSortOrder}
              className="bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
            >
              {sortOrder === "asc" ? "Ascending" : "Descending"}
            </button>
            <button
              onClick={() => router.push("/statistics")}
              className="bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
            >
              View Statistics
            </button>
          </div>
        </div>

        <div className="overflow-x-auto">
          <table className="min-w-full bg-[#1d1d1d] text-gray-200 shadow-md rounded-lg overflow-hidden table-fixed">
            <thead className="bg-gray-700 text-white text-left">
              <tr>
                <th className="py-2 px-4 text-left" style={{ width: "5%" }}>
                  #
                </th>
                <th className="py-2 px-4 text-left" style={{ width: "45%" }}>
                  Team
                </th>
                <th className="py-2 px-4 text-center" style={{ width: "10%" }}>
                  Played
                </th>
                <th className="py-2 px-4 text-center" style={{ width: "10%" }}>
                  Wins
                </th>
                <th className="py-2 px-4 text-center" style={{ width: "10%" }}>
                  Draws
                </th>
                <th className="py-2 px-4 text-center" style={{ width: "10%" }}>
                  Losses
                </th>
                <th className="py-2 px-4 text-center" style={{ width: "10%" }}>
                  Points
                </th>
              </tr>
            </thead>
            <tbody>
              {paginatedTeams.map((team) => {
                const points = team.wins * 3 + team.draws;
                const gamesPlayed = team.wins + team.draws + team.losses;
                const originalPosition = teams.findIndex((t) => t.name === team.name) + 1;
                let bgColor = "bg-[#1d1d1d]"; // Default color

                if (team.wins === maxWins) {
                  bgColor = "bg-green-600"; // Most wins
                } else if (team.wins === minWins) {
                  bgColor = "bg-red-500"; // Least wins
                } else if (Math.abs(team.wins - avgWins) < 1) {
                  bgColor = "bg-blue-700"; // Close to average
                }

                return (
                  <tr key={team.name} className={`${bgColor} border-b border-gray-700 hover:bg-gray-700`}>
                    <td className="py-2 px-4 text-left">{originalPosition}</td>
                    <td
                      className="py-2 px-4 font-medium cursor-pointer"
                      onClick={() => router.push(`/${team.name}`)} // Navigate to team's page
                    >
                      {team.name}
                    </td>
                    <td className="py-2 px-4 text-center">{gamesPlayed}</td>
                    <td className="py-2 px-4 text-center">{team.wins}</td>
                    <td className="py-2 px-4 text-center">{team.draws}</td>
                    <td className="py-2 px-4 text-center">{team.losses}</td>
                    <td className="py-2 px-4 text-center font-bold">{points}</td>
                    <td className="py-2 px-4 text-center">
                      <input
                        type="checkbox"
                        checked={selectedTeams.includes(team.name)}
                        onChange={() => handleCheckboxChange(team.name)} // Handle checkbox selection
                      />
                    </td>
                  </tr>
                );
              })}
            </tbody>
          </table>
        </div>
      {/* Pagination controls */}
      <div className="flex justify-center mt-4 gap-4">
          <button
            onClick={() => handlePageChange(currentPage - 1)}
            disabled={currentPage === 1}
            className={`px-4 py-2 rounded ${
              currentPage === 1 ? "bg-gray-500 cursor-not-allowed" : "bg-blue-500 text-white cursor-pointer"
            }`}
          >
            Previous
          </button>
          <span className="text-white">
            Page {currentPage} of {totalPages}
          </span>
          <button
            onClick={() => handlePageChange(currentPage + 1)}
            disabled={currentPage === totalPages}
            className={`px-4 py-2 rounded ${
              currentPage === totalPages ? "bg-gray-500 cursor-not-allowed" : "bg-blue-500 text-white cursor-pointer"
            }`}
          >
            Next
          </button>
        </div>
      </div>

      {isModalOpen && (
        <div className="fixed inset-0 bg-black bg-opacity-75 flex items-center justify-center z-50" aria-modal="true" role="dialog">
          <div className="bg-white text-black p-6 rounded-lg w-96">
            <h3 className="text-xl font-bold mb-4">Add New Team</h3>
            <div className="flex flex-col gap-2">
              {Object.keys(newTeam).map((key) => (
                <input
                  key={key}
                  type="text"
                  name={key}
                  placeholder={key}
                  value={newTeam[key as keyof typeof newTeam]}
                  onChange={handleInputChange}
                  className="p-2 border border-gray-300 rounded"
                />
              ))}
            </div>
            <div className="flex justify-end gap-4 mt-4">
              <button
                className="bg-gray-500 text-white px-4 py-2 rounded cursor-pointer"
                onClick={handleCloseModal}
              >
                Cancel
              </button>
              <button
                className="bg-green-500 text-white px-4 py-2 rounded cursor-pointer"
                onClick={handleSaveTeam}
              >
                Save
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}