// SVD implementation in C++ (no external libraries)
// Uses eigen-decomposition of A^T * A via the Jacobi method to obtain V and singular values,
// then computes U = A * V * Sigma^{-1} and constructs S.

#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<double>>;

static double EPS = 1e-12;

int rows(const Matrix &A) { return (int)A.size(); }
int cols(const Matrix &A) { return A.empty() ? 0 : (int)A[0].size(); }

Matrix zeros(int m, int n) { return Matrix(m, vector<double>(n, 0.0)); }

Matrix transpose(const Matrix &A)
{
    int m = rows(A), n = cols(A);
    Matrix B = zeros(n, m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            B[j][i] = A[i][j];
    return B;
}

Matrix multiply(const Matrix &A, const Matrix &B)
{
    int m = rows(A), p = cols(A), n = cols(B);
    Matrix C = zeros(m, n);
    for (int i = 0; i < m; ++i)
    {
        for (int k = 0; k < p; ++k)
        {
            double aik = A[i][k];
            if (aik == 0.0)
                continue;
            for (int j = 0; j < n; ++j)
                C[i][j] += aik * B[k][j];
        }
    }
    return C;
}

vector<double> matvec(const Matrix &A, const vector<double> &x)
{
    int m = rows(A), n = cols(A);
    vector<double> y(m, 0.0);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            y[i] += A[i][j] * x[j];
    return y;
}

double dot(const vector<double> &a, const vector<double> &b)
{
    double s = 0;
    int n = (int)a.size();
    for (int i = 0; i < n; ++i)
        s += a[i] * b[i];
    return s;
}

void normalize_inplace(vector<double> &v)
{
    double nrm = sqrt(dot(v, v));
    if (nrm < EPS)
        return;
    for (double &x : v)
        x /= nrm;
}

// Jacobi eigenvalue algorithm for symmetric matrices
// Returns eigenvalues in 'vals' and eigenvectors as columns of 'vecs' (n x n)
void jacobi_eigen(const Matrix &A, vector<double> &vals, Matrix &vecs, int max_iter = 100)
{
    int n = cols(A);
    Matrix a = A; // copy
    vecs = zeros(n, n);
    for (int i = 0; i < n; ++i)
        vecs[i][i] = 1.0;

    auto max_offdiag = [&](int &p, int &q)
    {
        double maxv = 0.0;
        p = q = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
            {
                double v = fabs(a[i][j]);
                if (v > maxv)
                {
                    maxv = v;
                    p = i;
                    q = j;
                }
            }
        return maxv;
    };

    for (int iter = 0; iter < max_iter; ++iter)
    {
        int p, q;
        double maxv = max_offdiag(p, q);
        if (maxv < 1e-14)
            break;
        double app = a[p][p], aqq = a[q][q], apq = a[p][q];
        double phi = 0.5 * atan2(2 * apq, aqq - app);
        double c = cos(phi), s = sin(phi);

        // rotate rows/cols p and q
        for (int k = 0; k < n; ++k)
        {
            double aik = a[p][k], aqk = a[q][k];
            a[p][k] = c * aik - s * aqk;
            a[q][k] = s * aik + c * aqk;
        }
        for (int k = 0; k < n; ++k)
        {
            double aki = a[k][p], akq = a[k][q];
            a[k][p] = c * aki - s * akq;
            a[k][q] = s * aki + c * akq;
        }
        a[p][p] = c * c * app - 2 * s * c * apq + s * s * aqq;
        a[q][q] = s * s * app + 2 * s * c * apq + c * c * aqq;
        a[p][q] = a[q][p] = 0.0;

        // update eigenvector matrix
        for (int k = 0; k < n; ++k)
        {
            double vkp = vecs[k][p], vkq = vecs[k][q];
            vecs[k][p] = c * vkp - s * vkq;
            vecs[k][q] = s * vkp + c * vkq;
        }
    }

    vals.assign(n, 0.0);
    for (int i = 0; i < n; ++i)
        vals[i] = a[i][i];
}

// Sort eigenvalues (and corresponding columns of vecs) in descending order
void sort_eigenpairs(vector<double> &vals, Matrix &vecs)
{
    int n = (int)vals.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j)
         { return vals[i] > vals[j]; });
    vector<double> vals2(n);
    Matrix vecs2 = zeros(n, n);
    for (int k = 0; k < n; ++k)
    {
        vals2[k] = vals[idx[k]];
        for (int i = 0; i < n; ++i)
            vecs2[i][k] = vecs[i][idx[k]];
    }
    vals.swap(vals2);
    vecs.swap(vecs2);
}

// Compute SVD of A (m x n). Returns U (m x m), S (m x n), Vt (n x n)
void svd(const Matrix &A, Matrix &U, Matrix &S, Matrix &Vt)
{
    int m = rows(A), n = cols(A);
    Matrix At = transpose(A);
    Matrix AtA = multiply(At, A); // n x n symmetric

    // eigen-decompose AtA
    vector<double> eigvals;
    Matrix V; // columns are eigenvectors
    jacobi_eigen(AtA, eigvals, V, 200);
    sort_eigenpairs(eigvals, V);

    // singular values
    int r = min(m, n);
    vector<double> sigma(r, 0.0);
    for (int i = 0; i < r; ++i)
        sigma[i] = (eigvals[i] > 0) ? sqrt(max(0.0, eigvals[i])) : 0.0;

    // build Vt (transpose of V)
    Vt = zeros(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            Vt[i][j] = V[j][i];

    // compute U columns for first r singular vectors
    U = zeros(m, m);
    for (int i = 0; i < r; ++i)
    {
        vector<double> vi(n);
        for (int j = 0; j < n; ++j)
            vi[j] = V[j][i];
        if (sigma[i] > 1e-15)
        {
            vector<double> Av = matvec(A, vi); // m
            for (int k = 0; k < m; ++k)
                U[k][i] = Av[k] / sigma[i];
        }
        else
        {
            // zero singular value: find orthonormal vector orthogonal to previous U columns
            vector<double> vec(m, 0.0);
            for (int k = 0; k < m; ++k)
                vec[k] = (double)rand() / RAND_MAX;
            // Gram-Schmidt
            for (int j = 0; j < i; ++j)
            {
                double proj = 0.0;
                for (int k = 0; k < m; ++k)
                    proj += U[k][j] * vec[k];
                for (int k = 0; k < m; ++k)
                    vec[k] -= proj * U[k][j];
            }
            normalize_inplace(vec);
            for (int k = 0; k < m; ++k)
                U[k][i] = vec[k];
        }
    }

    // complete U to m x m orthonormal basis if needed
    int cur = r;
    while (cur < m)
    {
        vector<double> vec(m, 0.0);
        for (int k = 0; k < m; ++k)
            vec[k] = (double)rand() / RAND_MAX;
        for (int j = 0; j < cur; ++j)
        {
            double proj = 0.0;
            for (int k = 0; k < m; ++k)
                proj += U[k][j] * vec[k];
            for (int k = 0; k < m; ++k)
                vec[k] -= proj * U[k][j];
        }
        normalize_inplace(vec);
        // skip near-zero vectors
        double nrm = sqrt(dot(vec, vec));
        if (nrm < 1e-10)
            continue;
        for (int k = 0; k < m; ++k)
            U[k][cur] = vec[k];
        ++cur;
    }

    // build S (m x n)
    S = zeros(m, n);
    for (int i = 0; i < r; ++i)
        S[i][i] = sigma[i];
}

// Utility: print matrix
void print_mat(const Matrix &A, const string &name)
{
    int m = rows(A), n = cols(A);
    cout << name << " (" << m << "x" << n << "):\n";
    cout.setf(std::ios::fixed);
    cout << setprecision(6);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            cout << setw(12) << A[i][j];
        cout << '\n';
    }
}

int main()
{
    // Example: 4x3 matrix
    Matrix A = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0}};

    Matrix U, S, Vt;
    svd(A, U, S, Vt);

    print_mat(A, "A");
    cout << "\n";
    print_mat(U, "U");
    cout << "\n";
    print_mat(S, "S");
    cout << "\n";
    print_mat(Vt, "V^T");

    // Optionally check A_reconstructed = U * S * Vt
    Matrix US = multiply(U, S);
    Matrix Arec = multiply(US, Vt);
    cout << "\nReconstructed A:\n";
    print_mat(Arec, "Arec");

    return 0;
}
