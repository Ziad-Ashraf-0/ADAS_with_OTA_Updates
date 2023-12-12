import React, { useState, useEffect } from "react";
import { Text, StyleSheet } from "react-native";

const DownloadLatestVER = ({ fetching }) => {
  const [dots, setDots] = useState(".");

  useEffect(() => {
    let interval;

    if (fetching) {
      interval = setInterval(() => {
        setDots((prevDots) => {
          if (prevDots.length === 4) {
            return ".";
          } else {
            return prevDots + ".";
          }
        });
      }, 500);
    }

    return () => {
      clearInterval(interval);
    };
  }, [fetching]);

  return (
    <Text style={styles.text}>
      {fetching ? "Downloading" + dots : "Downloaded"}
    </Text>
  );
};

const styles = StyleSheet.create({
  text: {
    backgroundColor: "transparent",
    fontSize: 24,
    fontWeight: "bold",
    color: "white",
    textShadowColor: "rgba(0, 0, 0, 0.5)",
    textShadowOffset: { width: 2, height: 2 },
    textShadowRadius: 5,
  },
});
export default DownloadLatestVER;
