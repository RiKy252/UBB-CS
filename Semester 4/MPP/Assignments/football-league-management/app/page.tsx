"use client";

import React, { useState, useEffect } from "react";
import { useRouter } from "next/navigation";
import { Team, RankedTeam } from "./api/teams/data";

export default function PremierLeagueTeams() {
  const [teams, setTeams] = useState<RankedTeam[]>([]);
  const [sortCriteria, setSortCriteria] = useState("points");
  const [sortOrder, setSortOrder] = useState<"asc" | "desc">("desc");
  const [searchQuery, setSearchQuery] = useState("");
  const [selectedTeams, setSelectedTeams] = useState<string[]>([]);
  const [currentPage, setCurrentPage] = useState(1);
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const router = useRouter();
  const teamsPerPage = 10;

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

  const fetchTeams = async () => {
    setIsLoading(true);
    setError(null);
    try {
  
      const response = await fetch(
        `/api/teams/`
      );
      
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
      
      const data = await response.json();
      setTeams(data);
    } catch (error) {
      console.error("Error fetching teams:", error);
      setError("Failed to fetch teams. Please try again later.");
    } finally {
      setIsLoading(false);
    }
  };

  const searchTeams = async () => {
    setIsLoading(true);
    setError(null);
  
    try {
      const queryParams = new URLSearchParams();
  
      if (searchQuery) queryParams.append("query", searchQuery);
      if (sortCriteria) queryParams.append("sortBy", sortCriteria);
      if (sortOrder) queryParams.append("order", sortOrder);
  
      const response = await fetch(`/api/teams/sort?${queryParams.toString()}`);
  
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
  
      const data = await response.json();
      setTeams(data);
    } catch (error) {
      console.error("Error searching and sorting teams:", error);
      setError("Failed to fetch teams. Please try again later.");
    } finally {
      setIsLoading(false);
    }
  };

  useEffect(() => {
  if (teams.length === 0) {
    // Initially fetch teams only once when the teams array is empty
    fetchTeams();
  } else {
    // After initial fetch, sort teams as per criteria
    searchTeams();
  }
}, [sortCriteria, sortOrder]); // This will run again whenever sortCriteria or sortOrder changes

  // Effect for fetching teams or searching based on criteria
  useEffect(() => {
    if (searchQuery || sortCriteria || sortOrder) {
      searchTeams();
    } else {
      fetchTeams();
    }
  }, [sortCriteria, sortOrder]); // Re-fetch when sorting changes

  // Handle search with debounce
  useEffect(() => {
    const timer = setTimeout(() => {
      if (searchQuery) {
        searchTeams();
      } else {
        fetchTeams();
      }
    }, 300);

    return () => clearTimeout(timer);
  }, [searchQuery]);

  if (isLoading) {
    return (
      <div className="bg-black text-white min-h-screen flex items-center justify-center">
        <h1 className="text-3xl font-bold">Loading teams...</h1>
      </div>
    );
  }

  if (error) {
    return (
      <div className="bg-black text-white min-h-screen flex items-center justify-center">
        <div className="text-center">
          <h1 className="text-3xl font-bold text-red-500">Error</h1>
          <p className="mt-2">{error}</p>
          <button 
            onClick={fetchTeams}
            className="mt-4 bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
          >
            Try Again
          </button>
        </div>
      </div>
    );
  }

  if (teams.length === 0) {
    return (
      <div className="bg-black text-white min-h-screen flex items-center justify-center">
        <h1 className="text-3xl font-bold">No Teams Available</h1>
      </div>
    );
  }

  // Pagination calculation
  const paginatedTeams = teams.slice(
    (currentPage - 1) * teamsPerPage,
    currentPage * teamsPerPage
  );

  const totalPages = Math.ceil(teams.length / teamsPerPage);

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

  const handleRemoveTeams = async () => {
    if (selectedTeams.length === 0) {
      alert("Please select at least one team to remove.");
      return;
    }

    setIsLoading(true);
    
    try {
      // Delete each selected team using the API
      for (const teamName of selectedTeams) {
        const teamToDelete = teams.find(team => team.name === teamName);
        if (teamToDelete) {
          const response = await fetch(`/api/teams/${teamToDelete.name}`, {
            method: 'DELETE',
          });
          
          if (!response.ok) {
            const errorData = await response.json();
            console.error("Delete error response:", errorData);
            throw new Error(`Failed to delete team: ${teamName}`);
          }
        }
      }
      
      // Refresh the teams list
      setSelectedTeams([]);
      await fetchTeams();
      
    } catch (error) {
      console.error("Error removing teams:", error);
      setError("Failed to remove teams. Please try again.");
    } finally {
      setIsLoading(false);
    }
  };

  const handleAddTeam = () => {
    setIsModalOpen(true);
  };

  const handleCloseModal = () => {
    setIsModalOpen(false);
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

  const handleSaveTeam = async () => {
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

    try {
      setIsLoading(true);
      
      // Create the new team object for the API
      const teamData = {
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

      // Send POST request to create new team
      const response = await fetch('/api/teams', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(teamData),
      });

      if (!response.ok) {
        throw new Error('Failed to create team');
      }

      // Refresh the teams list
      await fetchTeams();
      handleCloseModal();
      
    } catch (error) {
      console.error("Error adding team:", error);
      setError("Failed to add team. Please try again.");
    } finally {
      setIsLoading(false);
    }
  };

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
              disabled={selectedTeams.length === 0}
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
                <th className="py-2 px-4 text-center" style={{ width: "5%" }}>
                  Select
                </th>
              </tr>
            </thead>
            <tbody>
              {paginatedTeams.map((team) => {
                let bgColor = "bg-[#1d1d1d]"; // Default color

                if (team.metadata?.isMostWins) {
                  bgColor = "bg-green-600"; // Most wins
                } else if (team.metadata?.isLeastWins) {
                  bgColor = "bg-red-500"; // Least wins
                } else if (team.metadata?.isAvgWins) {
                  bgColor = "bg-blue-700"; // Close to average
                }
                return (
                  <tr key={team.name} className={`${bgColor} border-b border-gray-700 hover:bg-gray-700`}>
                    <td className="py-2 px-4 text-left">{team.position}</td>
                    <td
                      className="py-2 px-4 font-medium cursor-pointer"
                      onClick={() => router.push(`/${team.name}`)} // Navigate to team's page
                    >
                      {team.name}
                    </td>
                    <td className="py-2 px-4 text-center">{team.gamesPlayed}</td>
                    <td className="py-2 px-4 text-center">{team.wins}</td>
                    <td className="py-2 px-4 text-center">{team.draws}</td>
                    <td className="py-2 px-4 text-center">{team.losses}</td>
                    <td className="py-2 px-4 text-center font-bold">{team.points}</td>
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
                  placeholder={key.charAt(0).toUpperCase() + key.slice(1).replace(/([A-Z])/g, ' $1')}
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