'use strict';

module.exports = {
  up: async (queryInterface, Sequelize) => {
    await queryInterface.createTable('Teams', {
      id: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER
      },
      name: {
        type: Sequelize.STRING,
        allowNull: false
      },
      coachName: {
        type: Sequelize.STRING
      },
      homeStadium: {
        type: Sequelize.STRING
      },
      foundedYear: {
        type: Sequelize.INTEGER
      },
      wins: {
        type: Sequelize.INTEGER,
        defaultValue: 0
      },
      draws: {
        type: Sequelize.INTEGER,
        defaultValue: 0
      },
      losses: {
        type: Sequelize.INTEGER,
        defaultValue: 0
      },
      goalsScored: {
        type: Sequelize.INTEGER,
        defaultValue: 0
      },
      goalsConceded: {
        type: Sequelize.INTEGER,
        defaultValue: 0
      },
      players: {
        type: Sequelize.ARRAY(Sequelize.STRING), // Only works in PostgreSQL
        defaultValue: []
      },
      country: {
        type: Sequelize.STRING
      },
      createdAt: {
        allowNull: false,
        type: Sequelize.DATE,
        defaultValue: Sequelize.literal('NOW()')
      },
      updatedAt: {
        allowNull: false,
        type: Sequelize.DATE,
        defaultValue: Sequelize.literal('NOW()')
      }
    });
  },

  down: async (queryInterface, Sequelize) => {
    await queryInterface.dropTable('Teams');
  }
};
