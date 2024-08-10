import sys
import keras
import struct
import numpy as np
import tensorflow as tf
from tensorflow.keras.optimizers import Adam
from sklearn.model_selection import train_test_split
from keras.layers import Input, Conv2D, MaxPooling2D, UpSampling2D

def load_mnist_images(filename):                                               #Diabazoume apo ena MNIST arxeio tis eikones kai epistrefoume ta dianusmata tous
  image_data = np.array([])
  with open(filename, 'rb') as f:
    magic, num_images, rows, cols = struct.unpack('>IIII', f.read(16))
    image_data = np.frombuffer(f.read(), dtype=np.uint8).reshape(num_images, rows, cols)

  return image_data

(X_train, _), (X_test, _) = keras.datasets.mnist.load_data()                   #Fortwnoume sto X_train 60.000 eikones tupou MNIST kai sto X_test 10.000

X_train = X_train.reshape(X_train.shape[0], 28, 28, 1)                         #Kanoume thn kanonikopoihsh kai to reshape tou X_train
X_train = X_train.astype("float32") / 255

X_test = X_test.reshape(X_test.shape[0], 28, 28, 1)                            #Kanoume thn kanonikopoihsh kai to reshape tou X_test
X_test = X_test.astype("float32") / 255

train_data, valid_data, train_ground, valid_ground = train_test_split(X_train, X_train, test_size=0.3, random_state=13)  #Xwrizoume ta dedomena tou X_train se eikones gia training kai validation 

latent_dim = 10
epochs = 27
batch_size = 8

input_img = Input(shape=(28, 28, 1))

def encoder(input_img):                                                        #Sunartsh gia ton encoder
  # encoder
  conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(input_img)   
  pool1 = MaxPooling2D(pool_size=(2, 2))(conv1)
  conv2 = Conv2D(64, (3, 3), activation='relu', padding='same')(pool1)
  encoded = MaxPooling2D(pool_size=(2, 2))(conv2) 
  return encoded, conv2

def Autoencoder(encoded):                                                      #Sunartsh gia ton decoder
  # decoder
  conv4 = Conv2D(64, (3, 3), activation='relu', padding='same')(encoded)
  up1 = UpSampling2D((2, 2))(conv4)
  decoded = Conv2D(1, (3, 3), activation='sigmoid', padding='same')(up1)
  return decoded

def Neural_network():                                                          #Sunarthsh gia to training tou NN
  input_img = Input(shape=(28, 28, 1))
  (encoded),(conv) = encoder(input_img)
  decoded = Autoencoder(conv)

  autoencoder = keras.models.Model(input_img, decoded)
  autoencoder.compile(loss='mean_squared_error', optimizer=Adam())

  earlystopping = keras.callbacks.EarlyStopping(monitor="val_loss", mode="min", patience=5, restore_best_weights=True)
  autoencoder.fit(train_data, train_ground, batch_size=batch_size, epochs=epochs, verbose=1, validation_data=(valid_data, valid_ground), callbacks=[earlystopping])

  encoder_model = keras.models.Model(input_img, encoded)
  return autoencoder, encoder_model

def save_latent_vectors(model, data, output_file):                             #Thn xrhsimopoioume gia na apothikeuoume ta latent vector se ena .txt arxeio
  latent_vectors = model.predict(data, verbose=0)                              #To latent vectors exei shape: Number_imagesx14x14x64
  conv1 = Conv2D(latent_dim, (3, 3), activation='relu', padding='same')(latent_vectors)  #To conv1 exei shape: Number_imagesx14x14x64
  down1 = MaxPooling2D(pool_size=(14, 14))(conv1)                              #To down1 exei shape: Number_imagesx1x1xlatent_dim             
  latent_vectors = tf.reshape(down1, (down1.shape[0], -1))                     #To latent vectors exei shape: Number_imagesxlatent_dim
  latent_vectors = tf.cast(tf.round(latent_vectors * 255), dtype=tf.uint8)     #To apotelesma tou latent vector tha einai double se diasthma [0,1] to kanoume na einai se diasthma [0,255] kai akeraios
  np.savetxt(output_file, latent_vectors.numpy(), fmt='%d')                    #Apothikeuoume to latent_vectors se arxeio .txt pou tha exei grammes = NUMBER_IMAGES, sthles = latent_dim

def main():
  user_input = input("Type 'yes' if you want to create a new NN or 'no' otherwise: ")
  if user_input == "yes":                                                      #An o xrhsths thelei na ekpaideusei apo thn arxh to neurwniko diktuo
    autoencoder, encoder_model = Neural_network()
    autoencoder.save('autoencoder.h5')                                         #Afou to dhmiourghsei to apothikeuei kai se ena arxeio
  elif user_input == "no":                                                     #An o xrhsths den thelei na ekpaideusei apo thn arxh to neurwniko diktuo
    autoencoder = keras.models.load_model('autoencoder.h5', compile=False)     #Tote apla to fortwnei apo to antistoixo arxeio
  
  if sys.argv[1] != "-d":
    print("Invalid flag!Expected '-d'.\n")
    return;
  if sys.argv[3] != "-q":
    print("Invalid flag!Expected '-d'.\n")
    return;
  if sys.argv[5] != "-od":
    print("Invalid flag!Expected '-d'.\n")
    return;
  if sys.argv[7] != "-oq":
    print("Invalid flag!Expected '-d'.\n")
    return;
  
  file_dataset = sys.argv[2]                                                   #Diabazoume apo thn grammh entolwn to onoma tou arxeiou dataset
  file_queryset = sys.argv[4]                                                  #Diabazoume apo thn grammh entolwn to onoma tou arxeiou query
  out_dataset = sys.argv[6]                                                    #Diabazoume apo thn grammh entolwn to onoma tou arxeiou eksodou dataset
  out_queryset = sys.argv[8]                                                   #Diabazoume apo thn grammh entolwn to onoma tou arxeiou eksodou query

  images_dataset = np.array([])
  images_query = np.array([])
  images_dataset = load_mnist_images(file_dataset)                             #Apothikeuoume tis eikones tou arxeiou dataset ston katallhlo pinaka
  images_query = load_mnist_images(file_queryset)                              #Apothikeuoume tis eikones tou arxeiou query ston katallhlo pinaka

  images_dataset = images_dataset.reshape(images_dataset.shape[0], 28, 28, 1)  #Kanoume kanonikopoihsh kai reshape gia tis eikones dataset
  images_dataset = images_dataset.astype("float32") / 255
  images_query = images_query.reshape(images_query.shape[0], 28, 28, 1)        #Kanoume kanonikopoihsh kai reshape gia tis eikones query
  images_query = images_query.astype("float32") / 255

  encoder_model = keras.models.Model(inputs=autoencoder.input, outputs=autoencoder.layers[3].output)

  save_latent_vectors(encoder_model, images_query, out_queryset)               #Apothikeuoume ta latent vectors tou dataset sto katallhlo arxeio 
  save_latent_vectors(encoder_model, images_dataset, out_dataset)              #Apothikeuoume ta latent vectors tou query sto antistoixo arxeio 
 
if __name__ == "__main__":
  main()