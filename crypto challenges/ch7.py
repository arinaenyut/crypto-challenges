import base64

from Crypto.Cipher import AES

def decrypt_ecb(text,key):
	cipher=AES.new(key,AES.MODE_ECB)
	plaintext=cipher.decrypt(text)
	return plaintext

key=b'YELLOW SUBMARINE'
with open('/home/challenge7.txt') as tx:
	ciphertext=base64.b64decode(tx.read())
message=decrypt_ecb(ciphertext,key)
print(message)
