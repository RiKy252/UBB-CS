"use client";

import React, { useState, useEffect } from "react"; 
import { useParams } from "next/navigation";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPencilAlt } from "@fortawesome/free-solid-svg-icons";

export default function TeamPage() {
  const { id: teamName } = useParams();

  const [team, setTeam] = useState<any | null>(null);
  
  const [editingField, setEditingField] = useState<string | null>(null); // Track which field is being edited
  const [editedValue, setEditedValue] = useState<string>(""); // Track the new value for the field

  useEffect(() => {
    const fetchTeam = async () => {
      try {
        const res = await fetch(`/api/teams/${teamName}`);
        if (!res.ok) throw new Error("Failed to fetch team");

        const data = await res.json();
        setTeam(data);
      } catch (err) {
        console.error(err);
        alert("Error fetching team data.");
      }
    };

    if (teamName) {
      fetchTeam();
    }
  }, [teamName]);


  if (!team) {
    return (
      <div className="bg-black text-white min-h-screen flex items-center justify-center">
        <h1 className="text-3xl font-bold">Searching...</h1>
      </div>
    );
  }

  const handleEditClick = (field: string, currentValue: string) => {
    setEditingField(field);
    setEditedValue(currentValue);
  };

  const handlePlayerUpdate = async (index: number, newName: string) => {
    if (!newName.trim()) {
      alert("Player name cannot be empty.");
      return;
    }

    const updatedPlayers = [...team.players];
    updatedPlayers[index] = newName;

    try {
      const res = await fetch(`/api/teams/${team.name}`, {
        method: "PATCH",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ players: updatedPlayers }),
      });

      if (!res.ok) {
        throw new Error("Failed to update player");
      }

      const updatedTeam = await res.json();

      setTeam(updatedTeam);
      
      setEditingField(null);
      setEditedValue("");
    } catch (err) {
      alert("Error updating player: " + err);
    }
  };

  const handleSave = async () => {
    if (!editedValue.trim()) {
      alert("Input cannot be empty.");
      return;
    }

    // Validate numeric fields
    if (
      ["foundedYear", "wins", "draws", "losses", "goalsScored", "goalsConceded"].includes(editingField!) &&
      isNaN(Number(editedValue))
    ) {
      alert("This field must be a valid number.");
      return;
    }

    const updatedValue = ["foundedYear", "wins", "draws", "losses", "goalsScored", "goalsConceded"].includes(editingField!)
                              ? Number(editedValue)
                              : editedValue;

    try {
      const res = await fetch(`/api/teams/${team.name}`, {
        method: "PATCH",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ [editingField!]: updatedValue }),
      }); 

      if (!res.ok) {
        throw new Error("Failed to update team");
      }

      const updatedTeam = await res.json();
      setTeam(updatedTeam);

    } catch (err) {
      alert("Error updating team: " + err);
    }

    
    // Reset editing state
    setEditingField(null);
    setEditedValue("");
  };

  const handleCancel = () => {
    setEditingField(null);
    setEditedValue("");
  };

  return (
    <div className="bg-black text-white min-h-screen p-6">
      {/* Team Header */}
      <div className="bg-[#1d1d1d] p-6 rounded-lg shadow-md mb-6">
        {/* Team Name */}
        <div className="relative group">
            <h1 className="text-3xl font-bold inline-block">
              {team.name}
            </h1>
        </div>

        {/* Coach Name */}
        <div className="relative group mt-4">
          <p className="text-lg inline-block">
            Coach:{" "}
            {editingField === "coachName" ? (
              <input
                type="text"
                value={editedValue}
                onChange={(e) => setEditedValue(e.target.value)}
                className="bg-gray-700 text-white p-1 rounded"
              />
            ) : (
              team.coachName
            )}
          </p>
          {editingField !== "coachName" && (
            <FontAwesomeIcon
              icon={faPencilAlt}
              className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
              onClick={() => handleEditClick("coachName", team.coachName)}
            />
          )}
          {editingField === "coachName" && (
            <div className="inline-block ml-2">
              <button
                onClick={handleSave}
                className="bg-green-500 text-white px-2 py-1 rounded mr-2"
              >
                Save
              </button>
              <button
                onClick={handleCancel}
                className="bg-red-500 text-white px-2 py-1 rounded"
              >
                Cancel
              </button>
            </div>
          )}
        </div>

        {/* Stadium */}
        <div className="relative group mt-4">
          <p className="text-lg inline-block">
            Stadium:{" "}
            {editingField === "homeStadium" ? (
              <input
                type="text"
                value={editedValue}
                onChange={(e) => setEditedValue(e.target.value)}
                className="bg-gray-700 text-white p-1 rounded"
              />
            ) : (
              team.homeStadium
            )}
          </p>
          {editingField !== "homeStadium" && (
            <FontAwesomeIcon
              icon={faPencilAlt}
              className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
              onClick={() => handleEditClick("homeStadium", team.homeStadium)}
            />
          )}
          {editingField === "homeStadium" && (
            <div className="inline-block ml-2">
              <button
                onClick={handleSave}
                className="bg-green-500 text-white px-2 py-1 rounded mr-2"
              >
                Save
              </button>
              <button
                onClick={handleCancel}
                className="bg-red-500 text-white px-2 py-1 rounded"
              >
                Cancel
              </button>
            </div>
          )}
        </div>

        {/* Founded Year */}
        <div className="relative group mt-4">
          <p className="text-lg inline-block">
            Founded:{" "}
            {editingField === "foundedYear" ? (
              <input
                type="text"
                value={editedValue}
                onChange={(e) => setEditedValue(e.target.value)}
                className="bg-gray-700 text-white p-1 rounded"
              />
            ) : (
              team.foundedYear
            )}
          </p>
          {editingField !== "foundedYear" && (
            <FontAwesomeIcon
              icon={faPencilAlt}
              className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
              onClick={() => handleEditClick("foundedYear", String(team.foundedYear))}
            />
          )}
          {editingField === "foundedYear" && (
            <div className="inline-block ml-2">
              <button
                onClick={handleSave}
                className="bg-green-500 text-white px-2 py-1 rounded mr-2"
              >
                Save
              </button>
              <button
                onClick={handleCancel}
                className="bg-red-500 text-white px-2 py-1 rounded"
              >
                Cancel
              </button>
            </div>
          )}
        </div>
      </div>

      {/* Team Stats */}
      <div className="bg-[#1d1d1d] p-6 rounded-lg shadow-md mb-6">
        <h2 className="text-2xl font-bold mb-4">Team Stats</h2>
        <div className="grid grid-cols-2 gap-4">
          {/* Left Column */}
          <div>
            {/* Wins */}
            <div className="relative group">
              <p className="text-lg inline-block">
                Wins:{" "}
                {editingField === "wins" ? (
                  <input
                    type="text"
                    value={editedValue}
                    onChange={(e) => setEditedValue(e.target.value)}
                    className="bg-gray-700 text-white p-1 rounded"
                  />
                ) : (
                  team.wins
                )}
              </p>
              {editingField !== "wins" && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick("wins", String(team.wins))}
                />
              )}
              {editingField === "wins" && (
                <div className="inline-block ml-2">
                  <button
                    onClick={handleSave}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </div>

            {/* Draws */}
            <div className="relative group mt-4">
              <p className="text-lg inline-block">
                Draws:{" "}
                {editingField === "draws" ? (
                  <input
                    type="text"
                    value={editedValue}
                    onChange={(e) => setEditedValue(e.target.value)}
                    className="bg-gray-700 text-white p-1 rounded"
                  />
                ) : (
                  team.draws
                )}
              </p>
              {editingField !== "draws" && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick("draws", String(team.draws))}
                />
              )}
              {editingField === "draws" && (
                <div className="inline-block ml-2">
                  <button
                    onClick={handleSave}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </div>

            {/* Losses */}
            <div className="relative group mt-4">
              <p className="text-lg inline-block">
                Losses:{" "}
                {editingField === "losses" ? (
                  <input
                    type="text"
                    value={editedValue}
                    onChange={(e) => setEditedValue(e.target.value)}
                    className="bg-gray-700 text-white p-1 rounded"
                  />
                ) : (
                  team.losses
                )}
              </p>
              {editingField !== "losses" && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick("losses", String(team.losses))}
                />
              )}
              {editingField === "losses" && (
                <div className="inline-block ml-2">
                  <button
                    onClick={handleSave}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </div>
          </div>

          {/* Right Column */}
          <div>
            {/* Goals Scored */}
            <div className="relative group">
              <p className="text-lg inline-block">
                Goals Scored:{" "}
                {editingField === "goalsScored" ? (
                  <input
                    type="text"
                    value={editedValue}
                    onChange={(e) => setEditedValue(e.target.value)}
                    className="bg-gray-700 text-white p-1 rounded"
                  />
                ) : (
                  team.goalsScored
                )}
              </p>
              {editingField !== "goalsScored" && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick("goalsScored", String(team.goalsScored))}
                />
              )}
              {editingField === "goalsScored" && (
                <div className="inline-block ml-2">
                  <button
                    onClick={handleSave}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </div>

            {/* Goals Conceded */}
            <div className="relative group mt-4">
              <p className="text-lg inline-block">
                Goals Conceded:{" "}
                {editingField === "goalsConceded" ? (
                  <input
                    type="text"
                    value={editedValue}
                    onChange={(e) => setEditedValue(e.target.value)}
                    className="bg-gray-700 text-white p-1 rounded"
                  />
                ) : (
                  team.goalsConceded
                )}
              </p>
              {editingField !== "goalsConceded" && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick("goalsConceded", String(team.goalsConceded))}
                />
              )}
              {editingField === "goalsConceded" && (
                <div className="inline-block ml-2">
                  <button
                    onClick={handleSave}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </div>
          </div>
        </div>
      </div>

      {/* Players List */}
      <div className="bg-[#1d1d1d] p-6 rounded-lg shadow-md">
        <h2 className="text-2xl font-bold mb-4">Players</h2>
        <ul className="list-disc list-inside">
          {team.players.map((player: string, index: number) => (
            <li key={index} className="text-lg relative group">
              {editingField === `player-${index}` ? (
                <input
                  type="text"
                  value={editedValue}
                  onChange={(e) => setEditedValue(e.target.value)}
                  className="bg-gray-700 text-white p-1 rounded"
                />
              ) : (
                player
              )}
              {editingField !== `player-${index}` && (
                <FontAwesomeIcon
                  icon={faPencilAlt}
                  className="inline-block w-4 h-4 ml-2 cursor-pointer opacity-0 group-hover:opacity-100"
                  onClick={() => handleEditClick(`player-${index}`, player)}
                />
              )}
              {editingField === `player-${index}` && (
                <div className="inline-block ml-2">
                  <button
                    onClick={() => handlePlayerUpdate(index, editedValue)}
                    className="bg-green-500 text-white px-2 py-1 rounded mr-2"
                  >
                    Save
                  </button>
                  <button
                    onClick={handleCancel}
                    className="bg-red-500 text-white px-2 py-1 rounded"
                  >
                    Cancel
                  </button>
                </div>
              )}
            </li>
          ))}
        </ul>
        {/* <div className="mt-4">
          <button
            onClick={() => {
              setEditingField("new-player");
              setEditedValue("");
            }}
            className="bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
          >
            Add Player
          </button>
          {editingField === "new-player" && (
            <div className="mt-2">
              <input
                type="text"
                value={editedValue}
                onChange={(e) => setEditedValue(e.target.value)}
                className="bg-gray-700 text-white p-1 rounded mr-2"
              />
              <button
                // onClick={handleAddPlayer} todo when i will have a database
                className="bg-green-500 text-white px-2 py-1 rounded mr-2"
              >
                Save
              </button>
              <button
                onClick={handleCancel}
                className="bg-red-500 text-white px-2 py-1 rounded"
              >
                Cancel
              </button>
            </div>
          )}
        </div> */}
      </div>
    </div>
  );
}