import React, {useState} from 'react';
import {Text, StyleSheet, View} from 'react-native';

export default function Index() {
  const styles = StyleSheet.create({
    container: {
      flex: 1,
    },
    baseText: {
      fontFamily: 'Cochin',
    },
    titleText: {
      fontSize: 50,
      fontWeight: 'bold',
    },
  });
  return (
    <View
      style={{
        flex: 1,
        justifyContent: "center",
        alignItems: "center",
      }}
    >
      <Text style={styles.titleText}>Hello World!</Text>
    </View>
  );
}
