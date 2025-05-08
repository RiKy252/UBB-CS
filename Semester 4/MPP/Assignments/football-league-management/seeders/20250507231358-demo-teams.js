'use strict';

module.exports = {
  async up(queryInterface, Sequelize) {
    await queryInterface.bulkInsert('Teams', [
      {
        name: 'Real Madrid',
        coachName: 'Carlo Ancelotti',
        homeStadium: 'Santiago Bernabéu',
        foundedYear: 1902,
        wins: 25,
        draws: 5,
        losses: 4,
        goalsScored: 80,
        goalsConceded: 30,
        players: Sequelize.literal("ARRAY['Modrić','Benzema','Vinícius']"),
        country: 'Spain',
        createdAt: new Date(),
        updatedAt: new Date()
      },
      {
        name: 'Manchester City',
        coachName: 'Pep Guardiola',
        homeStadium: 'Etihad Stadium',
        foundedYear: 1880,
        wins: 27,
        draws: 4,
        losses: 3,
        goalsScored: 90,
        goalsConceded: 25,
        players: Sequelize.literal("ARRAY['Haaland','De Bruyne','Foden']"),
        country: 'England',
        createdAt: new Date(),
        updatedAt: new Date()
      }
    ], {});
  },

  async down(queryInterface, Sequelize) {
    await queryInterface.bulkDelete('Teams', null, {});
  }
};
