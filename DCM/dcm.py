import numpy as np

def get_bold(A_I, A_E, B_I, B_E, C, random_state):

    # U
    u_task = np.genfromtxt('u_task.csv', delimiter=',')
    u_pictures = np.genfromtxt('u_pictures.csv', delimiter=',')
    u_words = np.genfromtxt('u_words.csv', delimiter=',')
    u = np.array([u_task, u_pictures, u_words])

    # State vec
    state_vec = np.zeros((3200, 4))

    # Initial conditions
    state_vec[0, :] = 1

    def dzdt(t, z_prev):
        intr_sum = 0
        extr_sum = 0
        for ind in range(3):
            intr_sum = intr_sum + B_I[ind] * u[ind, t]
            extr_sum = extr_sum + B_E[ind] * u[ind, t]
        
        J = -0.5 * np.exp(A_I) * np.exp(intr_sum) + A_E + extr_sum
        # Rx1 = RxR @ Rx1 + RxJ @ Jx1
        return J @ z_prev + C @ u[:, t].reshape(-1, 1)

    dt = 3.6 / 1000
    for t in range(1, len(state_vec) - 1):
        state_vec[t, :] = state_vec[t - 1, :] + dzdt(t, state_vec[t - 1, :].reshape(-1, 1)).flatten() * dt

    # Hemo
    kappa = 0.64 * np.exp(random_state.normal(0, np.sqrt(1 / 256))) # Rate of vasodilatory signal decay (prior)
    gamma = 6 # Rate of decay to feedback to vasodilatory signal (?)

    s = np.zeros((3200, 4))
    f = np.zeros((3200, 4))

    s[0, :] = 1
    f[0, :] = 1

    def dsdt(x, s_prev, f_prev):
        dsdt = x - kappa * s_prev - gamma * (f_prev - np.ones(4))
        return dsdt

    def dfdt(s_prev):
        dfdt = s_prev
        return dfdt

    dt = 3.6 / 1000
    for t in range(1, len(s) - 1):
        s[t, :] = s[t - 1, :] + dsdt(state_vec[t - 1, :], s[t - 1, :], f[t - 1, :]) * dt
        f[t, :] = f[t - 1, :] + dfdt(s[t - 1, :]) * dt

    tau = 2 * np.exp(kappa) / 0.64 # hemodynamic transit time (seconds, static)
    alpha = 0.32 # Grubb's exponent (blood vessel stiffness, static)

    v = np.zeros((3200, 4))
    v[0, :] = 0.1

    def dvdt(v_prev, f_prev):
        return 1 / tau * (f_prev - v_prev) ** (1 / alpha)

    dt = 3.6 / 1000
    for t in range(1, len(s) - 1):
        v[t, :] = v[t - 1, :] + dvdt(v[t - 1, :], f[t - 1, :]) * dt

    E0 = 0.4 # Resting oxygen extraction fraction (static)

    def dqdt(q_prev, f_prev, v_prev):
        return (1 / tau) * (f_prev / E0) * (1 - (1 - E0) ** (1 / f_prev)) - v_prev ** (1 / alpha) * (q_prev / v_prev)

    q = np.zeros((3200, 4))

    dt = 3.6 / 1000
    for t in range(1, len(s) - 1):
        q[t, :] = q[t - 1, :] + dqdt(q[t - 1, :], f[t - 1, :], v[t - 1, :]) * dt

    TE = 0.04     # fMRI echo time (static)
    epsilon_h = 1 # Fraction of intravascular to extravascular signal (prior) --> original prior was zero changed to 1 --> looks like it's region dependent
    r0 = 25       # Oxygen extraction rate constant (static)
    nu0 = 40.3    # Blood volume normalized to rest (static)
    V0 = 4        # Resting venous volume (static)

    k1 = 4.3 * nu0 * E0 * TE
    k2 = epsilon_h * r0 * E0 * TE
    k3 = 1 - epsilon_h

    # Obtain the BOLD signal
    dS_S0 = V0 * (k1 * (1 - q) + k2 * (1 - q / v) + k3 * (1 - v))

    # Detrend the BOLD signal
    bold = np.diff(dS_S0, 2, axis = 0)

    return bold