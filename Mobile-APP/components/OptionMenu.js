import {LinearGradient} from 'expo-linear-gradient';
import React from 'react';
import {FlatList, StyleSheet, Text, TouchableOpacity, View} from 'react-native';

const DATA = [
  {id: '1', title: 'List Files'},
  {id: '2', title: 'Delete Files'},
  {id: '3', title: 'Download latest VER'},
  {id: '4', title: 'Send Binary'},
  {id: '5', title: 'Autopark'},
  {id: '6', title: 'Adaptive'},
  {id: '7', title: 'Button 7'},
  {id: '8', title: 'Button 8'},
  {id: '9', title: 'Button 9'},
  {id: '10', title: 'Button 10'},
  {id: '11', title: 'Button 11'},
  {id: '12', title: 'Button 12'},
  {id: '13', title: 'Button 13'},
  {id: '14', title: 'Button 14'},
  {id: '15', title: 'Button 15'},
];

const OptionMenu = ({onPressButton}) => {
  const renderItem = ({ item }) => (
    <TouchableOpacity style={styles.button} onPress={() => onPressButton(item.id)}>
      <LinearGradient colors={['#009FFD', '#2A2A72']} style={styles.buttonGradient}>
        <Text style={styles.buttonText}>{item.title}</Text>
      </LinearGradient>
    </TouchableOpacity>
  );

  return (
    <View style={styles.container}>
      <FlatList
        horizontal={true}
        data={DATA}
        renderItem={renderItem}
        keyExtractor={(item) => item.id}
        contentContainerStyle={styles.flatListContentContainer}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    backgroundColor: 'black',
    borderRadius: 10,
    paddingHorizontal: 10,
    paddingVertical: 20,
    marginHorizontal: 10,
    marginVertical: 20,
    shadowColor: '#000',
    shadowOffset: {
      width: 0,
      height: 3,
    },
    shadowOpacity: 0.1,
    shadowRadius: 4.65,
    elevation: 6,
  },
  flatListContentContainer: {
    alignItems: 'center',
  },
  button: {
    margin: 5,
    borderRadius: 5,
    overflow: 'hidden',
  },
  buttonGradient: {
    padding: 10,
    alignItems: 'center',
    borderRadius: 5,
  },
  buttonText: {
    color: 'white',
    fontWeight: 'bold',
  },
});

export default OptionMenu;
