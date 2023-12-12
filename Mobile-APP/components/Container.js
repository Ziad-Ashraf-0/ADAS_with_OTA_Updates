import React from "react";
import { LinearGradient } from "expo-linear-gradient";
import { SafeAreaView, StyleSheet } from "react-native";

//background: linear-gradient(180deg, #353A40 0%, #16171B 100%),
//linear-gradient(180deg, #424750 0%, #202326 100%);

const Container = ({ children }) => {
  return (
    <LinearGradient colors={["#202326", "#202326"]} style={styles.container}>
      {children}
    </LinearGradient>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 200,
  },
});

export default Container;
