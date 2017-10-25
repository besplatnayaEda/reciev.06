function cmd = CMD(comand)

charCMD = { 'NUMBER',                   ...     % 0
            'BODRATE',                  ...     % 1
            'REPEATNUM',                ...     % 2
            'F1S1',                     ...     % 3
            'F1S2',                     ...     % 4
            'F2S1',                     ...     % 5
            'F2S2',                     ...     % 6
            'FLP',                      ...     % 7
            'DETECTION_THRESHOLD',      ...     % 8
			'START_DATA_TRANSMIT_FLP',	...     % 9
			'STOP_DATA_TRANSMIT',       ...     % 10
			'START_DATA_TRANSMIT_F1',	...     % 11
			'START_DATA_TRANSMIT_F2',	...     % 12
			'START_DATA_TRANSMIT_IN',	...     % 13
			'GET_SETUP',                ...     % 14
			'GET_F1',                   ...     % 15
			'GET_F2',                   ...     % 16
			'GET_BR',                   ...     % 17
			'GET_NAME',                 ...     % 18
            'CONNECT',                  ...     % 19
			'OK',                       ...     % 20
			'ERR',                      ...     % 21
            'F1',                       ...     % 22
            'F2',                       ...     % 23
          };

[m, cmd] = max(strcmp(charCMD,comand));

cmd = m*cmd - 1;

end
