import React from "react";
import { TouchableOpacity, Image, StyleSheet } from "react-native";

const ScreenHeaderBtn = ({ iconUrl, dimension, handlePress }) => {
  return (
    <TouchableOpacity style={styles.btnContainer} onPress={handlePress}>
      <Image
        source={iconUrl}
        resizeMode="cover"
        style={styles.btnImg(dimension)}
      />
    </TouchableOpacity>
  );
};

const styles = StyleSheet.create({
  btnContainer: {
    width: 45,
    height: 45,
    backgroundColor: "black",
    borderRadius: 50,
    justifyContent: "center",
    alignItems: "center",
    borderWidth: 4,
    shadowColor: "white",
  },
  btnImg: (dimension) => ({
    width: dimension,
    height: dimension,
    borderRadius: 50,
  }),
});

export default ScreenHeaderBtn;
