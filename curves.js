/*
*  This is a PoC for a DH key exchange, constrained by Node 10's 
*  limited cryptographic primitives
*  If a more modern environment were available, a library like 
*  libsodium could be used for stronger key derivation functions, 
*  encryption algorithms, and potential performance benefits
*/

const crypto = require('crypto');

class SecureChannel {
	constructor(curveName = 'secp256k1') {
		this.curveName = curveName;
		this.keyPair = crypto.createECDH(this.curveName);
		this.keyPair.generateKeys();
	}

	getPublicKey() {
		return this.keyPair.getPublicKey('base64');
	}

	deriveEncryptionKey(otherPublicKey) {
		const sharedSecret = this.keyPair.computeSecret(otherPublicKey, 'base64', 'base64');
		return crypto.createHash('sha256').update(sharedSecret).digest();
	}

	encrypt(text, key) {
		// with AES-256-GCM, you'd normally be careful with your IV for it is a nonce.
		// In this implementation though, we'd always be using different keys (thus ephemeral)
		// so IV duplication is not a problem. If you have the same keys though, be careful.
		// Usually a counter to never have the same IV is a valid solution.
		const iv = crypto.randomBytes(16); 
		const cipher = crypto.createCipheriv('aes-256-gcm', key, iv);

		let encrypted = cipher.update(text, 'utf8', 'hex');
		encrypted += cipher.final('hex');

		const authTag = cipher.getAuthTag();

		return iv.toString('hex') + ':' + encrypted + ':' + authTag.toString('hex'); 
	}

	decrypt(data, key) {
		const [ivHex, encryptedHex, authTagHex] = data.split(':');
		const iv = Buffer.from(ivHex, 'hex');
		const authTag = Buffer.from(authTagHex, 'hex');
		const decipher = crypto.createDecipheriv('aes-256-gcm', key, iv);

		decipher.setAuthTag(authTag);
		let decrypted = decipher.update(encryptedHex, 'hex', 'utf8');
		decrypted += decipher.final('utf8'); 

		return decrypted;
	}
}

const keyDerivationStart = process.hrtime.bigint();

const alice = new SecureChannel();
const bob = new SecureChannel();

const alicePublicKey = alice.getPublicKey();
const bobPublicKey = bob.getPublicKey();

const aliceKey = alice.deriveEncryptionKey(bobPublicKey);
const bobKey = bob.deriveEncryptionKey(alicePublicKey);

const keyDerivationEnd = process.hrtime.bigint();
const keyDerivationTime = Number(keyDerivationEnd - keyDerivationStart) / 1000000;
console.log('Key Derivation Time:', keyDerivationTime.toFixed(3), 'ms'); 

console.log('Alice public key: ', Buffer.from(alicePublicKey).toString('base64'));
console.log('Bob public key: ', Buffer.from(bobPublicKey).toString('base64'));
console.log('');
console.log('Alice derived key: ', Buffer.from(aliceKey).toString('base64'));
console.log('Bob derived key: ', Buffer.from(bobKey).toString('base64'));
console.log('');

const encryptionStart = process.hrtime.bigint();

const encrypted = alice.encrypt('lain', aliceKey);

const encryptionEnd = process.hrtime.bigint();
const encryptionTime = Number(encryptionEnd - encryptionStart) / 1000000;
console.log('Encryption Time:', encryptionTime.toFixed(3), 'ms');

const decryptionStart = process.hrtime.bigint();

const decrypted = bob.decrypt(encrypted, bobKey);

const decryptionEnd = process.hrtime.bigint();
const decryptionTime = Number(decryptionEnd - decryptionStart) / 1000000;
console.log('Decryption Time:', decryptionTime.toFixed(3), 'ms');

console.log("Encrypted text:", encrypted);
console.log("Decrypted text:", decrypted);
