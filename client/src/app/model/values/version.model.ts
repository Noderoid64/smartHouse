export class Version {
    major: number;
    minor: number;
    patch: number;

    public toString(): string {
        return this.major + '.' + this.minor + '.' + this.patch;
    }

    public constructor(stringVersion: string) {
        const params: string[] = stringVersion.split('.');
        if (params.length !== 3) {
            console.error('version model could not be generated from: ' + stringVersion);
            this.major = this.minor = this.patch = 0;
        } else {
            this.major = +params[0];
            this.minor = +params[1];
            this.patch = +params[2];
        }
    }
}
